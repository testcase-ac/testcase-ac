#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 25);

    if (mode == 0) {
        if (rnd.next(0, 1) == 0) {
            n = 1;
            m = rnd.next(1, 25);
        } else {
            n = rnd.next(1, 10);
            m = 1;
        }
    } else if (mode == 1) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(5, 10);
        m = rnd.next(8, 25);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 25);
    }

    vector<string> board(n, string(m, '.'));

    if (mode == 0) {
        int ones = rnd.next(0, n * m);
        vector<int> cells;
        for (int i = 0; i < n * m; ++i) cells.push_back(i);
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < ones; ++i) board[cells[i] / m][cells[i] % m] = '1';
    } else if (mode == 1) {
        int p = rnd.next(0, 35);
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                if (rnd.next(0, 99) < p) board[r][c] = '1';
    } else if (mode == 2) {
        int p = rnd.next(45, 85);
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                if (rnd.next(0, 99) < p) board[r][c] = '1';
    } else if (mode == 3) {
        int phase = rnd.next(0, 1);
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                if ((r + c + phase) % 2 == 0 && rnd.next(0, 99) < 75) board[r][c] = '1';
    } else if (mode == 4) {
        int stripeEvery = rnd.next(2, 4);
        bool vertical = rnd.next(0, 1);
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                if ((vertical ? c : r) % stripeEvery == 0) board[r][c] = '1';
        int holes = rnd.next(0, max(1, n * m / 5));
        for (int i = 0; i < holes; ++i) board[rnd.next(0, n - 1)][rnd.next(0, m - 1)] = '.';
    } else if (mode == 5) {
        int clusters = rnd.next(1, 4);
        for (int k = 0; k < clusters; ++k) {
            int r1 = rnd.next(0, n - 1);
            int c1 = rnd.next(0, m - 1);
            int r2 = rnd.next(r1, min(n - 1, r1 + rnd.next(0, 3)));
            int c2 = rnd.next(c1, min(m - 1, c1 + rnd.next(0, 5)));
            for (int r = r1; r <= r2; ++r)
                for (int c = c1; c <= c2; ++c)
                    if (rnd.next(0, 99) < 80) board[r][c] = '1';
        }
    } else {
        int p = rnd.next(5, 60);
        for (int r = 0; r < n; ++r)
            for (int c = 0; c < m; ++c)
                if (rnd.next(0, 99) < p) board[r][c] = '1';
    }

    println(n, m);
    for (const string& row : board) println(row);

    return 0;
}
