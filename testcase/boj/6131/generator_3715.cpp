#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for distribution of N
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // uniform distribution
        N = rnd.next(1, 1000);
    } else if (mode == 1) {
        // biased towards smaller values
        // rnd.wnext(1000, -1) in [0,999], bias low
        N = rnd.wnext(1000, -1) + 1;
    } else {
        // biased towards larger values
        // rnd.wnext(1000, +1) in [0,999], bias high
        N = rnd.wnext(1000, +1) + 1;
    }
    println(N);
    return 0;
}
