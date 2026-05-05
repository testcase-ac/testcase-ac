#include "testlib.h"

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
  int N=rnd.next(1, 20),M=rnd.next(1, 5);
  printf("%d %d\n",N,M);
  for(int i=0;i<N;i++){
    for(int i=0;i<N;i++){
      printf("%d ",rnd.next(1, M));
    }
    printf("\n");
  }
  return 0; 
}
