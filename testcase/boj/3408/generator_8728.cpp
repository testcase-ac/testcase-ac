#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small for readability, randomized for variability
    int T = rnd.next(1, 4);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int pattern = rnd.next(0, 7); // 8 different generation patterns
        vector<int> a;
        int n = 0;

        switch (pattern) {
            // Pattern 0: all distinct, sometimes shuffled
            case 0: {
                n = rnd.next(1, 8);
                int base = rnd.next(0, 5);
                a.resize(n);
                for (int i = 0; i < n; ++i)
                    a[i] = base + i;
                if (n >= 3 && rnd.next(0, 1))
                    shuffle(a.begin(), a.end());
                break;
            }

            // Pattern 1: all equal
            case 1: {
                n = rnd.next(2, 10);
                int val = rnd.next(0, 9);
                a.assign(n, val);
                break;
            }

            // Pattern 2: palindrome (may have many duplicates)
            case 2: {
                n = rnd.next(3, 12);
                int k = rnd.next(1, 5); // value variety
                a.assign(n, 0);
                int half = (n + 1) / 2;
                for (int i = 0; i < half; ++i) {
                    int v = rnd.next(0, k - 1);
                    a[i] = a[n - 1 - i] = v;
                }
                break;
            }

            // Pattern 3: random small alphabet, shuffled
            case 3: {
                n = rnd.next(5, 18);
                int k = rnd.next(1, min(6, n)); // alphabet size
                a.resize(n);
                for (int i = 0; i < n; ++i)
                    a[i] = rnd.next(0, k - 1);
                break;
            }

            // Pattern 4: blocks of equal values
            case 4: {
                int limit = rnd.next(5, 18);
                int cur = 0;
                int base = rnd.next(0, 3);
                while (cur < limit) {
                    int len = rnd.next(1, 4);
                    if (cur + len > limit)
                        len = limit - cur;
                    int v = base + rnd.next(0, 4);
                    for (int j = 0; j < len; ++j)
                        a.push_back(v);
                    cur += len;
                }
                n = (int)a.size();
                break;
            }

            // Pattern 5: almost all equal, exactly one different
            case 5: {
                n = rnd.next(3, 12);
                int sameVal = rnd.next(0, 9);
                int uniqueVal = sameVal;
                while (uniqueVal == sameVal)
                    uniqueVal = rnd.next(0, 15);
                a.assign(n, sameVal);
                int pos = rnd.next(0, n - 1);
                a[pos] = uniqueVal;
                break;
            }

            // Pattern 6: medium random with small alphabet
            case 6: {
                n = rnd.next(10, 25);
                int k = rnd.next(2, 6);
                int base = rnd.next(0, 3) * 10;
                a.resize(n);
                for (int i = 0; i < n; ++i)
                    a[i] = base + rnd.next(0, k - 1);
                break;
            }

            // Pattern 7: small n, values are large (near 1e9), few distinct
            case 7: {
                n = rnd.next(1, 8);
                int k = rnd.next(1, min(4, n));
                vector<int> pool;
                for (int i = 0; i < k; ++i)
                    pool.push_back(rnd.next((int)1e8, (int)1e9 - 1));
                for (int i = 0; i < n; ++i)
                    a.push_back(rnd.any(pool));
                break;
            }
        }

        // Output the test case
        println(n);
        println(a);
    }

    return 0;
}
