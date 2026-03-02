#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

static void fail(const char *msg){
perror(msg);
exit(1);
}

static double secs_now(){
struct timespec ts;
if(clock_gettime(CLOCK_MONOTONIC,&ts)!=0) fail("clock_gettime");
return (double)ts.tv_sec + (double)ts.tv_nsec/1e9;
}

static void write_full(int fd,const void *buf,size_t n){
const unsigned char *p=(const unsigned char*)buf;
size_t i=0;
while(i<n){
ssize_t r=write(fd,p+i,n-i);
if(r<0){
if(errno==EINTR) continue;
fail("write");
}
i+=(size_t)r;
}
}

static void read_full(int fd,void *buf,size_t n){
unsigned char *p=(unsigned char*)buf;
size_t i=0;
while(i<n){
ssize_t r=read(fd,p+i,n-i);
if(r<0){
if(errno==EINTR) continue;
fail("read");
}
if(r==0){
fprintf(stderr,"read: hit EOF early\n");
exit(1);
}
i+=(size_t)r;
}
}

int main(int argc,char **argv){
long exchanges=1000000;
if(argc==2){
char *end=0;
long v=strtol(argv[1],&end,10);
if(!end || *end!='\0' || v<=0){
fprintf(stderr,"usage: %s [exchanges]\n",argv[0]);
return 1;
}
exchanges=v;
}

int p2c[2];
int c2p[2];
if(pipe(p2c)!=0) fail("pipe p2c");
if(pipe(c2p)!=0) fail("pipe c2p");

pid_t pid=fork();
if(pid<0) fail("fork");

unsigned char b=0xAB;

if(pid==0){
close(p2c[1]);
close(c2p[0]);

for(long i=0;i<exchanges;i++){
read_full(p2c[0],&b,1);
write_full(c2p[1],&b,1);
}

close(p2c[0]);
close(c2p[1]);
return 0;
}

close(p2c[0]);
close(c2p[1]);

double t0=secs_now();

for(long i=0;i<exchanges;i++){
write_full(p2c[1],&b,1);
read_full(c2p[0],&b,1);
}

double t1=secs_now();

close(p2c[1]);
close(c2p[0]);

int st=0;
waitpid(pid,&st,0);

double elapsed=t1-t0;
double rate=elapsed>0.0 ? (double)exchanges/elapsed : 0.0;

printf("Exchanges: %ld\n",exchanges);
printf("Elapsed: %.6f seconds\n",elapsed);
printf("Rate: %.2f exchanges/second\n",rate);
return 0;
}
