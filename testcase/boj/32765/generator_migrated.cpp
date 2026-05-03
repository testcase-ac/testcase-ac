#include "testlib.h"

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);
  int X = rnd.next(1, 1000000000);
  int Q = rnd.next(2, 20);
  printf("%d %d\n",X,Q);

  int tN = 1;
  for (int i = 1; i <= Q; i++) {
    if (i==19) {
      // 끝값 10억을 해야 하는데, 
      // validator 코드가 너무 비효율적이라 1억쯤 넘어가면 폭발함
      printf("99999999\n"); 
      continue;
    }
    printf("%d\n", tN);
    tN += rnd.next(1, 100*i*i);
  }
  return 0; 
}
