#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);
    int k = rnd.next(1, 18);

    if (mode == 1) {
        n = rnd.any(vector<int>{1, 2, 100000});
        m = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        m = rnd.any(vector<int>{1, 2, 100000});
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        m = rnd.next(2, 20);
        k = rnd.next(8, 25);
    } else if (mode == 4) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
        k = rnd.next(12, 30);
    } else if (mode == 5) {
        n = rnd.any(vector<int>{1, 2, 99999, 100000});
        m = rnd.any(vector<int>{1, 2, 99999, 100000});
        k = rnd.next(4, 12);
    }

    vector<pair<int, int>> classes;

    if (mode == 3) {
        int target = rnd.next(0, n + m - 2);
        for (int f = 1; f <= n; ++f) {
            int d = m + f - 1 - target;
            if (1 <= d && d <= m) {
                classes.emplace_back(f, d);
            }
        }
        shuffle(classes.begin(), classes.end());
    }

    if (mode == 4) {
        vector<pair<int, int>> cells;
        for (int f = 1; f <= n; ++f) {
            for (int d = 1; d <= m; ++d) {
                cells.emplace_back(f, d);
            }
        }
        shuffle(cells.begin(), cells.end());
        while ((int)classes.size() < k) {
            classes.push_back(rnd.any(cells));
        }
    }

    while ((int)classes.size() < k) {
        int edgeBias = rnd.next(0, 99);
        int f;
        int d;

        if (edgeBias < 20) {
            f = 1;
        } else if (edgeBias < 40) {
            f = n;
        } else {
            f = rnd.next(1, n);
        }

        if (edgeBias >= 40 && edgeBias < 60) {
            d = 1;
        } else if (edgeBias < 80) {
            d = m;
        } else {
            d = rnd.next(1, m);
        }

        classes.emplace_back(f, d);
    }

    shuffle(classes.begin(), classes.end());
    classes.resize(k);

    println(n, m, k);
    for (const auto& [f, d] : classes) {
        println(f, d);
    }

    return 0;
}
