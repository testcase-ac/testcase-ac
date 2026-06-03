#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(3, mode == 4 ? 30 : 12);

    vector<int> faction(n, 0);
    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            faction[i] = 0;
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            faction[i] = 1;
        }
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) {
            faction[i] = i % 2;
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = split; i < n; ++i) {
            faction[i] = 1;
        }
    } else {
        for (int i = 1; i < n; ++i) {
            faction[i] = rnd.next(2);
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                cout << ' ';
            }
            if (i == j) {
                cout << '0';
            } else {
                cout << (faction[i] == faction[j] ? '+' : '-');
            }
        }
        cout << '\n';
    }

    vector<pair<int, int>> candidates;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                candidates.push_back({i, j});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int m = rnd.next(1, 100);
    println(m);
    for (int q = 0; q < m; ++q) {
        if (q < (int)candidates.size()) {
            println(candidates[q].first, candidates[q].second);
        } else {
            int b = rnd.next(0, n - 1);
            int c = rnd.next(0, n - 2);
            if (c >= b) {
                ++c;
            }
            println(b, c);
        }
    }

    return 0;
}
