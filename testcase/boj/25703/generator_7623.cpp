#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Use weighted randomness on N to expose edge and mid cases:
    // t<0 biases small, t=0 uniform, t>0 biases large
    int t = rnd.next(-3, 3);
    int N = rnd.wnext(100, t) + 1;  // yields [1..100]
    println(N);
    return 0;
}
