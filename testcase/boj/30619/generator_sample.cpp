#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sizeChoices = {1, 2, 3, rnd.next(4, 12), rnd.next(13, 35)};
    int n = rnd.any(sizeChoices);

    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    int mode = rnd.next(5);
    if (mode == 1) {
        reverse(a.begin(), a.end());
    } else if (mode == 2) {
        rotate(a.begin(), a.begin() + rnd.next(n), a.end());
    } else if (mode == 3) {
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            swap(a[rnd.next(n)], a[rnd.next(n)]);
        }
    }

    int m = rnd.next(1, min(60, max(1, 3 * n)));
    vector<pair<int, int>> queries;
    queries.reserve(m);

    for (int i = 0; i < m; ++i) {
        int l = 1;
        int r = n;
        int queryMode = rnd.next(6);

        if (queryMode == 0) {
            l = r = rnd.next(1, n);
        } else if (queryMode == 1) {
            l = 1;
            r = n;
        } else if (queryMode == 2) {
            l = rnd.next(1, n);
            r = min(n, l + rnd.next(0, min(4, n - l)));
        } else if (queryMode == 3) {
            l = 1;
            r = rnd.next(1, n);
        } else if (queryMode == 4) {
            l = rnd.next(1, n);
            r = n;
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }

        queries.emplace_back(l, r);
    }

    println(n);
    println(a);
    println(m);
    for (auto [l, r] : queries) {
        println(l, r);
    }

    return 0;
}
