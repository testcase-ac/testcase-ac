#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(2, 6);
    println(T);

    for (int tc = 0; tc < T; tc++) {
        // Choose size category: 0 -> n=1, 1 -> small, 2 -> medium, 3 -> larger
        int nType = rnd.next(0, 3);
        int n;
        switch (nType) {
            case 0: n = 1; break;
            case 1: n = rnd.next(2, 5); break;
            case 2: n = rnd.next(6, 15); break;
            default: n = rnd.next(16, 30); break;
        }

        // Choose value pattern: 0 = uniform random, 1 = alternating high/low, 
        // 2 = non-decreasing, 3 = all same
        int valPattern = rnd.next(0, 3);

        vector<int> a(n), b(n);

        if (valPattern == 3) {
            // All the same value
            int v = rnd.next(0, 100);
            for (int i = 0; i < n; i++) {
                a[i] = v;
                b[i] = v;
            }
        }
        else if (valPattern == 1) {
            // Alternating high/low
            for (int i = 0; i < n; i++) {
                if (i % 2 == 0) {
                    a[i] = rnd.next(50, 100);
                    b[i] = rnd.next(0, 50);
                } else {
                    a[i] = rnd.next(0, 50);
                    b[i] = rnd.next(50, 100);
                }
            }
        }
        else if (valPattern == 2) {
            // Non-decreasing sequences
            int prevA = rnd.next(0, 100);
            int prevB = rnd.next(0, 100);
            a[0] = prevA;
            b[0] = prevB;
            for (int i = 1; i < n; i++) {
                a[i] = rnd.next(prevA, 100);
                b[i] = rnd.next(prevB, 100);
                prevA = a[i];
                prevB = b[i];
            }
        }
        else {
            // Uniform random
            for (int i = 0; i < n; i++) {
                a[i] = rnd.next(0, 100);
                b[i] = rnd.next(0, 100);
            }
        }

        // Output this test case
        println(n);
        println(a);
        println(b);
    }

    return 0;
}
