#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else {
        n = rnd.next(4, 18);
    }

    int w;
    if (mode == 0) {
        w = 1;
    } else if (mode == 1) {
        w = n - 1;
    } else if (mode == 2) {
        w = rnd.next(1, max(1, n / 3));
    } else if (mode == 3) {
        w = rnd.next(max(1, n - 4), n - 1);
    } else {
        w = rnd.next(1, n - 1);
    }

    vector<int> rows(n), cols(n);
    for (int i = 0; i < n; ++i) {
        rows[i] = i;
        cols[i] = i;
    }

    if (mode == 4) {
        reverse(cols.begin(), cols.end());
        int shift = rnd.next(0, n - 1);
        rotate(cols.begin(), cols.begin() + shift, cols.end());
    } else {
        shuffle(rows.begin(), rows.end());
        shuffle(cols.begin(), cols.end());
    }

    if (mode == 5 && n >= 6) {
        rows.clear();
        cols.clear();
        for (int i = 0; i < n; i += 2) {
            rows.push_back(i);
        }
        for (int i = 1; i < n; i += 2) {
            rows.push_back(i);
        }
        for (int i = n - 1; i >= 0; i -= 2) {
            cols.push_back(i);
        }
        for (int i = n - 2; i >= 0; i -= 2) {
            cols.push_back(i);
        }
    }

    vector<string> board(n, string(n, '.'));
    for (int i = 0; i < w; ++i) {
        board[rows[i]][cols[i]] = 'W';
    }

    println(n);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
