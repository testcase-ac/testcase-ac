#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode <= 3) {
        n = rnd.next(2, 8);
    } else {
        n = rnd.next(9, 15);
    }

    vector<int> s(n);
    iota(s.begin(), s.end(), 0);

    if (mode == 1) {
        reverse(s.begin(), s.end());
    } else if (mode == 2) {
        int shift = rnd.next(0, n - 1);
        rotate(s.begin(), s.begin() + shift, s.end());
    } else if (mode != 0 || rnd.next(0, 1)) {
        shuffle(s.begin(), s.end());
    }

    int m = 0;
    vector<pair<int, int>> swaps;
    if (!is_sorted(s.begin(), s.end()) || rnd.next(0, 3) != 0) {
        m = rnd.next(n, min(30 * n, max(n, 4 * n + 8)));
        swaps.reserve(m);
        for (int i = 0; i < m; ++i) {
            if (mode == 3) {
                int x = rnd.next(0, n - 1);
                swaps.push_back({x, x});
            } else if (mode == 4 && n > 1) {
                swaps.push_back({0, rnd.next(0, n - 1)});
            } else if (mode == 5 && n > 1) {
                int x = rnd.next(0, n - 2);
                swaps.push_back({x, x + 1});
            } else {
                swaps.push_back({rnd.next(0, n - 1), rnd.next(0, n - 1)});
            }
        }
    }

    println(n);
    println(s);
    println(m);
    for (auto [x, y] : swaps) {
        println(x, y);
    }

    return 0;
}
