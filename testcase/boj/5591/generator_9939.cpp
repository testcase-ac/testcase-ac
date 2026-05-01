#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 9);
    int n = 0, k = 0;
    vector<int> a;

    switch (scenario) {
        case 0: { // Very small n
            n = rnd.next(1, 3);
            k = rnd.next(1, n);
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.next(-3, 3);
            break;
        }
        case 1: { // All positive
            n = rnd.next(5, 20);
            int mode = rnd.next(0, 2);
            if (mode == 0) k = 1;
            else if (mode == 1) k = n;
            else k = rnd.next(1, n);
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.next(1, 10);
            break;
        }
        case 2: { // All non-positive
            n = rnd.next(5, 20);
            k = rnd.next(1, n);
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = -rnd.next(0, 10); // in [ -10, 0 ]
            break;
        }
        case 3: { // Negative with one big positive block
            n = rnd.next(8, 30);
            a.assign(n, 0);
            for (int i = 0; i < n; ++i)
                a[i] = -rnd.next(1, 9);

            int L = rnd.next(2, min(6, n));
            int start = rnd.next(0, n - L);
            for (int i = 0; i < L; ++i)
                a[start + i] = rnd.next(5, 15);

            if (rnd.next(0, 1) == 0)
                k = rnd.next(1, L);
            else
                k = rnd.next(L + 1, n);
            break;
        }
        case 4: { // Alternating signs
            n = rnd.next(6, 20);
            k = rnd.next(1, n);
            a.resize(n);
            bool posFirst = rnd.next(0, 1);
            for (int i = 0; i < n; ++i) {
                int val = rnd.next(1, 10);
                bool pos = (i % 2 == 0) ? posFirst : !posFirst;
                a[i] = pos ? val : -val;
            }
            break;
        }
        case 5: { // Many zeros with few non-zeros
            n = rnd.next(5, 25);
            k = rnd.next(1, n);
            a.assign(n, 0);
            int nonZeroCount = rnd.next(1, min(4, n));
            vector<int> idx(n);
            for (int i = 0; i < n; ++i) idx[i] = i;
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < nonZeroCount; ++i) {
                int pos = idx[i];
                int val;
                do {
                    val = rnd.next(-10, 10);
                } while (val == 0);
                a[pos] = val;
            }
            break;
        }
        case 6: { // k close to n
            n = rnd.next(2, 25);
            if (rnd.next(0, 1) == 0) k = n;
            else k = n - 1;
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.next(-10, 10);
            break;
        }
        case 7: { // Small k (1,2,3)
            n = rnd.next(5, 30);
            int cand[3] = {1, 2, 3};
            k = cand[rnd.next(0, 2)];
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.next(-20, 20);
            break;
        }
        case 8: { // Random with some extreme values
            n = rnd.next(5, 30);
            k = rnd.next(1, n);
            a.resize(n);
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 3) == 0) {
                    // extreme value
                    if (rnd.next(0, 1) == 0)
                        a[i] = rnd.next(9000, 10000);
                    else
                        a[i] = -rnd.next(9000, 10000);
                } else {
                    a[i] = rnd.next(-50, 50);
                }
            }
            break;
        }
        case 9: { // Best sum is 0 (zeros vs negatives)
            n = rnd.next(5, 20);
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = -rnd.next(1, 5);

            int Z = rnd.next(1, min(4, n));
            int start = rnd.next(0, n - Z);
            for (int i = 0; i < Z; ++i)
                a[start + i] = 0;

            if (rnd.next(0, 2) != 0)
                k = rnd.next(1, Z);
            else
                k = rnd.next(1, n);
            break;
        }
    }

    println(n, k);
    for (int i = 0; i < n; ++i)
        println(a[i]);

    return 0;
}
