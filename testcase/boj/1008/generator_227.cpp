#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int a = rnd.next(1, 9), b = rnd.next(1, 9);
    while(a == 2) {
      a = rnd.next(1, 9);
      b = rnd.next(1, 9);
    }  
    println(a, b);
}
