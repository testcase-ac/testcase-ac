#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n;
    int m;
    if (mode == 0) {
        n = 3;
        m = rnd.next(3, 10);
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        m = rnd.next(n, 12);
    } else {
        n = rnd.next(3, 20);
        m = rnd.next(n, 1000 / n);
    }

    vector<int> labels(n * m);
    for (int i = 0; i < n * m; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());

    vector<vector<int>> board(n, vector<int>(m));
    int ptr = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            board[r][c] = labels[ptr++];
        }
    }

    vector<vector<int>> neighbors(n * m + 1);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            vector<int> cur;
            cur.push_back(c + 1 < m ? board[r][c + 1] : 0);
            cur.push_back(r + 1 < n ? board[r + 1][c] : 0);
            cur.push_back(c > 0 ? board[r][c - 1] : 0);
            cur.push_back(r > 0 ? board[r - 1][c] : 0);
            shuffle(cur.begin(), cur.end());
            neighbors[board[r][c]] = cur;
        }
    }

    println(n, m);
    for (int piece = 1; piece <= n * m; ++piece) {
        println(neighbors[piece]);
    }
    println(board[0][0], board[0][1]);

    return 0;
}
