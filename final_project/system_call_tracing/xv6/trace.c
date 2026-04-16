#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"
int
main(int argc, char *argv[])
{
trace((1 << SYS_write) | (1 << SYS_open) | (1 << SYS_read) | (1 << SYS_close) | (1 << SYS_trace));

printf(1, "trace test starting\n");

int fd = open("README", 0);
if(fd >= 0){
char buf[16];
read(fd, buf, sizeof(buf));
close(fd);
}

printf(1, "trace test done\n");
exit();
}
