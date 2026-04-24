#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(5, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose N small but diverse
        int N;
        if (rnd.next() < 0.5) N = rnd.next(1, 5);
        else N = rnd.next(6, 10);
        println(N);
        // Choose starting point a
        int a;
        if (N == 1) {
            a = 1;
        } else {
            double p = rnd.next();
            if (p < 0.2) a = 1;
            else if (p < 0.4) a = N;
            else a = rnd.next(1, N);
        }
        println(a);
        // Generate the N-1 travel times
        if (N >= 2) {
            int mode = rnd.next(0, 2);
            vector<int> t(N - 1);
            if (mode == 0) {
                // Mixed uniform: some small, some larger
                for (int i = 0; i < N - 1; i++) {
                    if (rnd.next() < 0.3) t[i] = rnd.next(10, 20);
                    else t[i] = rnd.next(1, 10);
                }
            } else if (mode == 1) {
                // Monotonic increasing
                int base = rnd.next(1, 5);
                int delta = rnd.next(1, 3);
                for (int i = 0; i < N - 1; i++) {
                    int v = base + i * delta + rnd.next(0, 2);
                    t[i] = min(20, max(1, v));
                }
            } else {
                // Monotonic decreasing
                int base = rnd.next(10, 20);
                int delta = rnd.next(1, 3);
                for (int i = 0; i < N - 1; i++) {
                    int v = base - i * delta + rnd.next(0, 2);
                    t[i] = min(20, max(1, v));
                }
            }
            // Output times
            for (int x : t) println(x);
        }
    }
    return 0;
}
