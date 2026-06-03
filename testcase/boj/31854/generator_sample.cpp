#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 5);
    } else {
        n = rnd.next(2, 9);
    }

    vector<vector<int>> rank(n, vector<int>(n));
    vector<int> values(n * n);
    iota(values.begin(), values.end(), 1);

    if (mode == 0) {
        shuffle(values.begin(), values.end());
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                rank[r][c] = values[r * n + c];
            }
        }
    } else if (mode == 1) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                rank[r][c] = r * n + c + 1;
            }
        }
        if (rnd.next(2)) {
            reverse(rank.begin(), rank.end());
        }
        if (rnd.next(2)) {
            for (int r = 0; r < n; ++r) {
                reverse(rank[r].begin(), rank[r].end());
            }
        }
    } else if (mode == 2) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                int offset = (r % 2 == 0) ? c : n - 1 - c;
                rank[r][c] = r * n + offset + 1;
            }
        }
    } else {
        shuffle(values.begin(), values.end());
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                rank[r][c] = values[r * n + c];
            }
        }
    }

    println(n);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c + 1 < n; ++c) {
            if (c > 0) {
                cout << ' ';
            }
            cout << (rank[r][c] > rank[r][c + 1] ? '>' : '<');
        }
        cout << '\n';
    }
    for (int r = 0; r + 1 < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (c > 0) {
                cout << ' ';
            }
            cout << (rank[r][c] > rank[r + 1][c] ? '>' : '<');
        }
        cout << '\n';
    }

    return 0;
}
