#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

vector<int> makeStickLengths(int m, int mode) {
    vector<int> candidates(m);
    iota(candidates.begin(), candidates.end(), 1);
    shuffle(candidates.begin(), candidates.end());

    int k;
    if (mode == 0) {
        k = rnd.next(1, min(m, 4));
    } else if (mode == 1) {
        k = rnd.next(min(m, 3), min(m, 8));
    } else {
        k = rnd.next(1, min(m, 10));
    }

    vector<int> p(candidates.begin(), candidates.begin() + k);
    sort(p.begin(), p.end());
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        m = rnd.next(8, 18);
    } else {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
    }

    vector<string> board(n, string(m, '.'));
    if (mode == 1 || mode == 3) {
        int obstaclePercent = rnd.next(15, 65);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (rnd.next(100) < obstaclePercent) {
                    board[i][j] = '@';
                }
            }
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int gap = rnd.next(2, 5);
            int offset = rnd.next(0, gap - 1);
            for (int j = offset; j < m; j += gap) {
                board[i][j] = '@';
            }
        }
    }

    vector<int> p = makeStickLengths(m, mode);

    println(n, m);
    for (const string& row : board) {
        println(row);
    }
    println(static_cast<int>(p.size()));
    println(p);

    return 0;
}
