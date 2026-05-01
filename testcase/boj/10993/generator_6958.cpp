#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter t biases towards small or large N, t=0 yields uniform distribution.
    int t = rnd.next(-3, 3);
    // rnd.wnext(10, t) gives [0..9], biased by t; +1 maps to [1..10].
    int N = rnd.wnext(10, t) + 1;
    println(N);
    return 0;
}
