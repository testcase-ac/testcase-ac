#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode <= 2) {
        n = rnd.next(2, 6);
    } else if (mode <= 6) {
        n = rnd.next(3, 15);
    } else {
        n = rnd.next(16, 30);
    }

    vector<string> board(n, string(n, '.'));

    auto put = [&](int r, int c) {
        board[r][c] = 'G';
    };

    if (mode == 0) {
        put(0, 0);
    } else if (mode == 1) {
        put(rnd.next(0, n - 1), rnd.next(0, n - 1));
    } else if (mode == 2) {
        int r = rnd.next(0, n - 1);
        int c1 = rnd.next(0, n - 1);
        int c2 = rnd.next(0, n - 1);
        put(r, c1);
        put(r, c2);
    } else if (mode == 3) {
        int c = rnd.next(0, n - 1);
        int r1 = rnd.next(0, n - 1);
        int r2 = rnd.next(0, n - 1);
        put(r1, c);
        put(r2, c);
    } else if (mode == 4) {
        vector<pair<int, int>> corners = {{0, 0}, {0, n - 1}, {n - 1, 0}, {n - 1, n - 1}};
        shuffle(corners.begin(), corners.end());
        int take = rnd.next(1, 4);
        for (int i = 0; i < take; ++i) {
            put(corners[i].first, corners[i].second);
        }
    } else if (mode == 5) {
        int r1 = rnd.next(0, n - 1);
        int r2 = rnd.next(r1, n - 1);
        int c1 = rnd.next(0, n - 1);
        int c2 = rnd.next(c1, n - 1);
        for (int r = r1; r <= r2; ++r) {
            put(r, c1);
            put(r, c2);
        }
        for (int c = c1; c <= c2; ++c) {
            put(r1, c);
            put(r2, c);
        }
    } else if (mode == 6) {
        double density = rnd.next(0.08, 0.35);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (rnd.next() < density) {
                    put(r, c);
                }
            }
        }
    } else {
        double density = rnd.next(0.55, 0.95);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (rnd.next() < density) {
                    put(r, c);
                }
            }
        }
    }

    bool hasGomgom = false;
    for (const string& row : board) {
        hasGomgom = hasGomgom || row.find('G') != string::npos;
    }
    if (!hasGomgom) {
        put(rnd.next(0, n - 1), rnd.next(0, n - 1));
    }

    println(n);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
