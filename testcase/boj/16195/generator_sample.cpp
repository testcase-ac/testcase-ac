#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int mode = rnd.next(0, 5);
    int t = rnd.next(6, 18);

    if (mode == 0) {
        int n = rnd.next(1, 12);
        for (int m = 1; m <= n && (int)cases.size() < t; ++m) {
            cases.push_back({n, m});
        }
    } else if (mode == 1) {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 40);
            int minTerms = (n + 2) / 3;
            int lo = max(1, minTerms - 2);
            int hi = min(n, minTerms + 3);
            cases.push_back({n, rnd.next(lo, hi)});
        }
    } else if (mode == 2) {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 80);
            int m = rnd.next(1, min(n, 8));
            cases.push_back({n, m});
        }
    } else if (mode == 3) {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 120);
            int m = rnd.next(max(1, n - 8), n);
            cases.push_back({n, m});
        }
    } else if (mode == 4) {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(900, 1000);
            int m = rnd.next(1, n);
            if (rnd.next(0, 3) == 0) m = n;
            cases.push_back({n, m});
        }
    } else {
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(1, 1000);
            int m = rnd.next(1, n);
            cases.push_back({n, m});
        }
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, m] : cases) {
        println(n, m);
    }

    return 0;
}
