#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = 1;
        a.push_back(rnd.next(1, 2) == 1 ? 1LL : 1000000000LL);
    } else {
        n = rnd.next(2, 12);
        a.assign(n, 1);

        if (mode == 1) {
            long long value = rnd.next(1, 20);
            fill(a.begin(), a.end(), value);
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(1, 30);
            }
        } else if (mode == 3) {
            long long others = 0;
            for (int i = 0; i + 1 < n; ++i) {
                a[i] = rnd.next(1, 15);
                others += a[i];
            }
            a[n - 1] = others + rnd.next(1, 25);
        } else if (mode == 4) {
            long long others = 0;
            for (int i = 0; i + 1 < n; ++i) {
                a[i] = rnd.next(1, 20);
                others += a[i];
            }
            a[n - 1] = max(1LL, others + rnd.next(-3, 3));
        } else {
            for (int i = 0; i < n; ++i) {
                a[i] = rnd.next(1, 1000000000);
            }
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
