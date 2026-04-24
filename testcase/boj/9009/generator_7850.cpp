#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Precompute Fibonacci-like sequence for selection (1,2,3,5,...)
    vector<int> fib;
    fib.push_back(1);
    fib.push_back(2);
    while (true) {
        long long nxt = (long long)fib[fib.size()-1] + fib[fib.size()-2];
        if (nxt > 1000000000) break;
        fib.push_back((int)nxt);
    }
    int T = rnd.next(1, 8);
    println(T);
    for (int i = 0; i < T; i++) {
        double p = rnd.next();
        int n;
        if (p < 0.15) {
            // exact Fibonacci
            int k = rnd.next(0, (int)fib.size() - 1);
            n = fib[k];
        } else if (p < 0.3) {
            // just below a Fibonacci
            int k = rnd.next(1, (int)fib.size() - 1);
            n = fib[k] - 1;
        } else if (p < 0.45) {
            // just above a Fibonacci
            int k = rnd.next(0, (int)fib.size() - 1);
            long long tmp = (long long)fib[k] + 1;
            n = tmp > 1000000000 ? 1000000000 : (int)tmp;
        } else {
            // random size bucket
            double q = rnd.next();
            if (q < 0.4) {
                n = rnd.next(1, 20);
            } else if (q < 0.8) {
                n = rnd.next(21, 10000);
            } else {
                n = rnd.next(10001, 1000000000);
            }
        }
        println(n);
    }
    return 0;
}
