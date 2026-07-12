#include "testlib.h"

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
  int a=rnd.next(1,10000);
  int b=rnd.next(a,10000);
  int k=rnd.next(1,10000), x=rnd.next(1,10000);
  printf("%d %d\n%d %d\n",a,b,k,x);
  return 0; 
}
