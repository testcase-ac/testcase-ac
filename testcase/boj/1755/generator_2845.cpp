#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Hyperparameter: pick a generation mode for diversity
    int mode = rnd.next(0, 2);
    int M, N;
    if (mode == 0) {
        // small range: length up to ~10
        M = rnd.next(1, 99);
        int len = rnd.next(1, 10);
        N = rnd.next(M, min(99, M + len));
    } else if (mode == 1) {
        // medium range: length ~10 to ~50
        M = rnd.next(1, 80);
        int add1 = rnd.next(10, 20);
        int add2 = rnd.next(10, 50);
        int low = M + add1;
        int high = min(99, M + add2);
        if (low > high) low = min(M, high);
        N = rnd.next(low, high);
    } else {
        // full/random range
        M = rnd.next(1, 98);
        N = rnd.next(M, 99);
    }
    
    // Hyperparameter: sometimes force an extreme endpoint
    if (rnd.next() < 0.1) {
        if (rnd.next(0, 1) == 0) M = 1;
        else N = 99;
    }
    if (N < M) swap(M, N);
    
    // Output the single test case
    println(M, N);
    return 0;
}
