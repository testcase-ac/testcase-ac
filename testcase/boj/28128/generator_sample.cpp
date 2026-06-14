#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string nameFor(int id) {
    string s;
    do {
        s.push_back(char('a' + id % 26));
        id /= 26;
    } while (id > 0);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
    } else {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    }

    vector<vector<string>> board(n, vector<string>(m));
    int id = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            board[i][j] = nameFor(id++);
        }
    }

    if (mode == 2 && m >= 2) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 2);
        board[row][col + 1] = board[row][col];
    } else if (mode == 3 && n >= 2) {
        int row = rnd.next(0, n - 2);
        int col = rnd.next(0, m - 1);
        board[row + 1][col] = board[row][col];
    } else if (mode == 4 && m >= 3) {
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, m - 3);
        board[row][col + 2] = board[row][col];
    } else if (mode == 5 && n >= 3) {
        int row = rnd.next(0, n - 3);
        int col = rnd.next(0, m - 1);
        board[row + 2][col] = board[row][col];
    }

    int extraRepeats = rnd.next(0, max(1, n * m / 6));
    for (int k = 0; k < extraRepeats; ++k) {
        int r1 = rnd.next(0, n - 1);
        int c1 = rnd.next(0, m - 1);
        int r2 = rnd.next(0, n - 1);
        int c2 = rnd.next(0, m - 1);
        board[r2][c2] = board[r1][c1];
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(board[i]);
    }

    return 0;
}
