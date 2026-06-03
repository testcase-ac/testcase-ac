#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 7);
    } else {
        n = rnd.next(5, 18);
    }

    vector<string> mines(n, string(n, '.'));

    if (n >= 3) {
        if (mode == 2) {
            for (int i = 1; i + 1 < n; ++i)
                for (int j = 1; j + 1 < n; ++j)
                    mines[i][j] = '*';
        } else {
            int percent;
            if (mode == 0) {
                percent = rnd.next(0, 25);
            } else if (mode == 1) {
                percent = rnd.next(0, 55);
            } else if (mode == 3) {
                percent = rnd.next(55, 90);
            } else if (mode == 4) {
                percent = rnd.next(10, 70);
            } else {
                percent = rnd.next(0, 100);
            }

            for (int i = 1; i + 1 < n; ++i) {
                for (int j = 1; j + 1 < n; ++j) {
                    bool nearBorder = i == 1 || i == n - 2 || j == 1 || j == n - 2;
                    int localPercent = percent;
                    if (mode == 4) localPercent = nearBorder ? percent : percent / 4;
                    if (rnd.next(0, 99) < localPercent) mines[i][j] = '*';
                }
            }
        }
    }

    vector<string> board(n, string(n, '#'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool border = i == 0 || i == n - 1 || j == 0 || j == n - 1;
            if (!border) continue;

            int count = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue;
                    int ni = i + di;
                    int nj = j + dj;
                    if (0 <= ni && ni < n && 0 <= nj && nj < n && mines[ni][nj] == '*') {
                        ++count;
                    }
                }
            }
            board[i][j] = char('0' + count);
        }
    }

    println(n);
    for (const string& row : board) println(row);

    return 0;
}
