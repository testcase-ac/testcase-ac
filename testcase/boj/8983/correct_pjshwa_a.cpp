#include<stdio.h>
#include<algorithm>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;
class fio {
  size_t rsize;
  unsigned char* rbuf;
  int ridx;

  public:
  fio() : ridx(0) {
    struct stat rstat;
    fstat(0, &rstat);
    rsize = rstat.st_size;
    rbuf = (unsigned char*)mmap(0,rsize,PROT_READ,MAP_FILE|MAP_PRIVATE,0,0);
  }

  inline bool isBlank() {
    return
      rbuf[ridx] == '\n' || rbuf[ridx] == '\t' || rbuf[ridx] == '\r' ||
      rbuf[ridx] == '\f' || rbuf[ridx] == '\v' || rbuf[ridx] == ' ';
  }
  inline void consumeBlank() { while (isBlank()) ridx++; }

  inline int readInt(){
    int res = 0, flag = 0;
    consumeBlank();
    if (rbuf[ridx] == '-'){
      flag = 1;
      ridx++;
    }
    while (!isBlank() && ridx < rsize)
      res = 10 * res + rbuf[ridx++] - '0';
    return flag ? -res : res;
  }
};
struct P{
	int s,e;
	bool operator<(const P& tmp) const{
		return s<tmp.s;
	}
};
P S[100010]; //하자 
int m,t,l;
int n,arr[100010];
int main(){
	fio f;
	m=f.readInt();
	t=f.readInt();
	l=f.readInt();
	for(int i=0;i<m;i++)
		arr[i]=f.readInt();
	for(int i=0,x,y,z;i<t;i++){
		x=f.readInt(); y=f.readInt();
		z=l-y; 
		if(z>=0)
			S[n++]={x-z,x+z};
	}
	sort(arr,arr+m);
	sort(S,S+n);
	int ans=0,p=0;
	for(int i=0;i<n && p<m;){
		if(arr[p] >= S[i].s){
			if(arr[p] <= S[i].e)ans++;
			i++;
		}
		else p++;
	}
	printf("%d",ans);
} 
