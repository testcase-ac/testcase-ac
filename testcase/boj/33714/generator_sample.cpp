#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    long long k;
    vector<long long> a;
    a.reserve(n);

    if (mode == 0) {
        int prefix = rnd.next(0, min(n, 12));
        for (int i = 0; i < prefix; ++i) a.push_back(i);
        while ((int)a.size() < n) a.push_back(rnd.next(0, max(0, prefix + 3)));
        k = rnd.next(0, min(20, n + 5));
    } else if (mode == 1) {
        int gap = rnd.next(0, 10);
        for (int i = 0; (int)a.size() < n && i <= 12; ++i) {
            if (i != gap) a.push_back(i);
        }
        while ((int)a.size() < n) a.push_back(rnd.next(gap + 1, gap + 20));
        k = rnd.next(0, 12);
    } else if (mode == 2) {
        long long repeated = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.next(0, 12));
            } else {
                a.push_back(repeated);
            }
        }
        k = rnd.next(0, min(20, 2 * n));
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(20, 100));
        k = rnd.any(vector<long long>{0LL, 1LL, (long long)rnd.next(2, 20), 1000000000LL});
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<long long>{0LL, 1LL, 2LL, 999999999LL, 1000000000LL}));
        }
        k = rnd.any(vector<long long>{0LL, 1LL, (long long)n, 1000000000LL});
    } else {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, 1000000000));
        k = rnd.next(0, 1000000000);
    }

    shuffle(a.begin(), a.end());

    println(n, k);
    println(a);
    return 0;
}
