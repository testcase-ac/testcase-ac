#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a pattern to stress different scenarios
    int r = rnd.next(1, 100);
    int N;
    if (r <= 20) {
        // small N for trivial/edge cases
        N = rnd.next(0, 20);
    } else if (r <= 60) {
        // random N in full range
        N = rnd.next(0, 1000000);
    } else if (r <= 75) {
        // perfect square
        int k = rnd.next(0, 1000);
        N = k * k;
    } else if (r <= 90) {
        // power of 3
        int k = rnd.next(0, 12); // 3^12 ~ 531k
        int p = 1;
        for (int i = 0; i < k; i++) p *= 3;
        N = p;
    } else {
        // near upper bound
        N = 1000000 - rnd.next(0, 100);
    }
    println(N);
    return 0;
}
