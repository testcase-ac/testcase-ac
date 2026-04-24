#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter to bias N towards small or large within [1,20]
    int bias = rnd.next(-3, 3);
    int N = rnd.wnext(20, bias) + 1;  // yields in [1,20]
    // Output the single test case
    println(N);
    return 0;
}
