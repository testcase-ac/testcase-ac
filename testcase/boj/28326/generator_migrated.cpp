#include "testlib.h"

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
  int N=rnd.next(1,250000),M=rnd.next(1,250000);
  printf("%d %d\n",N,M);
  while(N--){
    int s=rnd.next(0,1000000000);
    int e=rnd.next(s,1000000000);
    int t=rnd.next(1,1000000000);
    printf("%d %d %d\n",s,e,t);
  }
  while(M--){
    int a=rnd.next(0,1000000000-1);
    int b=rnd.next(a,1000000000-1);
    printf("%d %d\n",a,b);
  }
  return 0;
}
