#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
      int N = rnd.next(0, 5);
      N = 2*N+1;
      println(N);
      for(int i=0; i<N; i++) {
          println(rnd.next(-9, 9));
      }
}
