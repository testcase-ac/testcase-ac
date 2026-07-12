#include "testlib.h"
int main(int argc, char* argv[]){
  registerGen(argc,argv,1);
  int list[6]={8, 26, 213, 2012, 99991, 99999};
  printf("%d\n",list[rnd.next(0,5)]);
  return 0;
}
