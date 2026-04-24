#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of dots between 2 and 10
    int n = rnd.next(2, 10);
    // Choose a pattern type for diversity
    int type = rnd.next(0, 2);

    vector<long long> xs;
    if (type == 0) {
        // Random increasing gaps
        long long cur = rnd.next(1, 5);
        xs.push_back(cur);
        for (int i = 1; i < n; i++) {
            cur += rnd.next(1, 10);
            xs.push_back(cur);
        }
    } else if (type == 1) {
        // Two-cluster pattern: small gaps, big gap, small gaps
        int c1 = rnd.next(2, n);
        long long cur = rnd.next(1, 5);
        xs.push_back(cur);
        for (int i = 1; i < c1; i++) {
            cur += rnd.next(1, 3);
            xs.push_back(cur);
        }
        if (c1 < n) {
            cur += rnd.next(10, 100);
            xs.push_back(cur);
            for (int i = c1 + 1; i < n; i++) {
                cur += rnd.next(1, 3);
                xs.push_back(cur);
            }
        }
    } else {
        // Arithmetic progression
        long long start = rnd.next(1, 10);
        int d = rnd.next(1, 5);
        for (int i = 0; i < n; i++) {
            xs.push_back(start + 1LL * i * d);
        }
    }

    // Output
    println(n);
    println(xs);

    return 0;
}
