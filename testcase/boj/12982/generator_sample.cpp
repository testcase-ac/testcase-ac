#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;
    vector<long long> x;

    if (mode == 0) {
        k = 1;
        x.push_back(rnd.next(1, 1000000000));
    } else {
        if (mode == 5) {
            k = rnd.next(20, 80);
        } else {
            k = rnd.next(2, 12);
        }
        x.resize(k);

        if (mode == 1) {
            long long value = rnd.next(1, 1000000000);
            fill(x.begin(), x.end(), value);
        } else if (mode == 2) {
            long long base = rnd.next(0, 1000) * 1LL * k;
            for (int i = 0; i < k; ++i) {
                x[i] = max(1LL, base + rnd.next(0, k - 1));
            }
        } else if (mode == 3) {
            for (int i = 0; i < k; ++i) {
                x[i] = rnd.next(1, 4);
            }
            int heavy = rnd.next(0, k - 1);
            x[heavy] = rnd.next(999999000, 1000000000);
        } else if (mode == 4) {
            for (int i = 0; i < k; ++i) {
                long long quotient = rnd.next(0, 20);
                x[i] = quotient * k + (i % k) + 1;
            }
            shuffle(x.begin(), x.end());
        } else {
            for (int i = 0; i < k; ++i) {
                if (rnd.next(0, 3) == 0) {
                    x[i] = rnd.next(900000000, 1000000000);
                } else {
                    x[i] = rnd.next(1, 200);
                }
            }
        }
    }

    println(k);
    println(x);
    return 0;
}
