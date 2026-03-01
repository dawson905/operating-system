#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <deque>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
using namespace std;

static auto T0=chrono::steady_clock::now();

static string ts(){
auto s=chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now()-T0).count();
int mm=(int)(s/60), ss=(int)(s%60);
ostringstream o;
o<<"["<<setw(2)<<setfill('0')<<mm<<":"<<setw(2)<<setfill('0')<<ss<<"]";
return o.str();
}
static void logp(int id,const string& m){
cout<<ts()<<" Philosopher "<<(id+1)<<" "<<m<<"\n";
cout.flush();
}

struct Fork{int id;};

class Table{
int n;
vector<bool> eating, queued;
deque<int> q;
mutex m;
condition_variable cv;
int L(int i)const{return (i+n-1)%n;}
int R(int i)const{return (i+1)%n;}
public:
explicit Table(int n):n(n),eating(n,false),queued(n,false){}
void request(int id){
unique_lock<mutex> lk(m);
if(!queued[id]){q.push_back(id);queued[id]=true;}
cv.wait(lk,[&]{return !q.empty() && q.front()==id && !eating[L(id)] && !eating[R(id)];});
eating[id]=true;
q.pop_front();
queued[id]=false;
cv.notify_all();
  }
void done(int id){
lock_guard<mutex> lk(m);
eating[id]=false;
cv.notify_all();
  }
};

class Philosopher{
int id, meals;
Fork &lf, &rf;
Table &t;
public:
Philosopher(int id,int meals,Fork& lf,Fork& rf,Table& t):id(id),meals(meals),lf(lf),rf(rf),t(t){}
void operator()(){
mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count()+id*997);
uniform_int_distribution<int> thinkMs(200,700), eatMs(300,900);
for(int k=0;k<meals;k++){
logp(id,"is Thinking.");
this_thread::sleep_for(chrono::milliseconds(thinkMs(rng)));
t.request(id);
logp(id,"picked up Left Fork.");
logp(id,"picked up Right Fork.");
logp(id,"is Eating.");
this_thread::sleep_for(chrono::milliseconds(eatMs(rng)));
logp(id,"put down Right Fork.");
logp(id,"put down Left Fork.");
t.done(id);
    }
logp(id,"is Done.");
  }
};

int main(){
const int N=5, MEALS=5;
vector<Fork> f(N);
for(int i=0;i<N;i++) f[i].id=i;
Table table(N);
vector<thread> th;
for(int i=0;i<N;i++){
th.emplace_back(Philosopher(i,MEALS,f[i],f[(i+1)%N],table));
  }
for(auto& x:th) x.join();
cout<<ts()<<" All philosophers finished.\n";
return 0;
}
