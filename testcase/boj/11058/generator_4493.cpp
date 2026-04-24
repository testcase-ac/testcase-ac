#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose input size category
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        // small N: 1 to 10
        N = rnd.next(1, 10);
    } else if (mode == 1) {
        // medium N: 11 to 50
        N = rnd.next(11, 50);
    } else {
        // large N: 51 to 100
        N = rnd.next(51, 100);
    }
    println(N);
    return 0;
}
