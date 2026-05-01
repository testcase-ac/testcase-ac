#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a single integer N in [0, 5], with bias toward edge and mid values
    int mode = rnd.next(0, 9);
    int N;
    if (mode == 0) {
        N = 0;          // smallest
    } else if (mode == 1) {
        N = 5;          // largest
    } else if (mode <= 3) {
        N = 1;          // small
    } else if (mode <= 5) {
        N = 2;          // small-mid
    } else if (mode <= 7) {
        N = 3;          // mid
    } else if (mode == 8) {
        N = 4;          // large-mid
    } else {
        N = rnd.next(0, 5); // fully random fallback
    }

    println(N);
    return 0;
}
