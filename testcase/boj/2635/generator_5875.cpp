#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        // trivial case
        N = 1;
    } else if (p < 0.2) {
        // small N
        N = rnd.next(2, 10);
    } else if (p < 0.3) {
        // powers of two
        int e = rnd.next(1, 14);
        N = 1 << e;
    } else if (p < 0.4) {
        // Fibonacci numbers up to 30000
        vector<int> fib = {1, 2};
        while (true) {
            int sz = fib.size();
            int nxt = fib[sz - 1] + fib[sz - 2];
            if (nxt > 30000) break;
            fib.push_back(nxt);
        }
        N = rnd.any(fib);
    } else if (p < 0.6) {
        // medium range
        N = rnd.next(11, 1000);
    } else if (p < 0.85) {
        // large range
        N = rnd.next(1001, 30000);
    } else {
        // near the upper bound
        N = rnd.next(29000, 30000);
    }
    println(N);
    return 0;
}
