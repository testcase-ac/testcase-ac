#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int r = 1;
    int c = 1;

    if (mode == 0) {
        r = 1;
        c = rnd.next(2, 18);
    } else if (mode == 1) {
        r = rnd.next(2, 18);
        c = 1;
    } else {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
    }

    int n = r * c;
    vector<int> values(n);
    int base = rnd.next(0, 300000 - n);
    iota(values.begin(), values.end(), base);

    vector<vector<int>> board(r, vector<int>(c));

    if (mode == 2) {
        int sinkRow = rnd.next(0, r - 1);
        int sinkCol = rnd.next(0, c - 1);
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int lhs, int rhs) {
            int lr = lhs / c, lc = lhs % c;
            int rr = rhs / c, rc = rhs % c;
            int ld = max(abs(lr - sinkRow), abs(lc - sinkCol));
            int rd = max(abs(rr - sinkRow), abs(rc - sinkCol));
            if (ld != rd) return ld < rd;
            return lhs < rhs;
        });
        for (int i = 0; i < n; ++i) {
            board[order[i] / c][order[i] % c] = values[i];
        }
    } else if (mode == 3) {
        shuffle(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            int row = i / c;
            int col = i % c;
            board[row][col] = values[n - 1 - i];
        }
    } else if (mode == 4) {
        int low = 0;
        int high = n - 1;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                bool useLow = ((i + j) % 2 == 0);
                board[i][j] = useLow ? values[low++] : values[high--];
            }
        }
    } else {
        shuffle(values.begin(), values.end());
        for (int i = 0; i < n; ++i) {
            board[i / c][i % c] = values[i];
        }
    }

    println(r, c);
    for (int i = 0; i < r; ++i) {
        println(board[i]);
    }

    return 0;
}
