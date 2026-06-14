#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n, m;
    if (mode == 0) {
        n = rnd.next(1, 2);
        m = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 2);
    } else if (mode == 2) {
        n = rnd.next(7, 8);
        m = rnd.next(7, 8);
    } else {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
    }

    vector<string> board(n, string(m, '.'));
    if (mode == 3) {
        char fill = rnd.next(0, 1) ? '*' : '.';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                board[i][j] = fill;
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                board[i][j] = ((i + j + rnd.next(0, 1)) % 2 == 0) ? '*' : '.';
            }
        }
    } else if (mode == 5) {
        int r1 = rnd.next(0, n - 1);
        int r2 = rnd.next(r1, n - 1);
        int c1 = rnd.next(0, m - 1);
        int c2 = rnd.next(c1, m - 1);
        for (int i = r1; i <= r2; ++i) {
            for (int j = c1; j <= c2; ++j) {
                board[i][j] = '*';
            }
        }
    } else {
        int percentOn = rnd.next(10, 90);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                board[i][j] = rnd.next(1, 100) <= percentOn ? '*' : '.';
            }
        }
    }

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
