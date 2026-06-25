#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static string randomRow(int m, const string& alphabet) {
    string row;
    row.reserve(m);
    for (int j = 0; j < m; ++j) {
        row.push_back(rnd.any(alphabet));
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int m = rnd.next(2, 12);

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 30);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        m = 1;
    } else if (mode == 5) {
        n = rnd.next(12, 24);
        m = rnd.next(12, 24);
    }

    vector<string> board(n, string(m, 'a'));
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    if (mode == 0 || mode == 1) {
        string smallAlphabet = alphabet.substr(0, rnd.next(2, 8));
        for (int i = 0; i < n; ++i) {
            board[i] = randomRow(m, smallAlphabet);
        }
    } else if (mode == 2) {
        char low = char('a' + rnd.next(0, 2));
        char high = char('x' + rnd.next(0, 2));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                board[i][j] = ((i + j) % 2 == 0) ? low : high;
            }
        }
        int changes = rnd.next(1, max(1, n * m / 3));
        for (int k = 0; k < changes; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            board[r][c] = char('a' + rnd.next(0, 25));
        }
    } else if (mode == 3) {
        int pathRow = 0;
        int pathCol = 0;
        board.assign(n, string(m, 'z'));
        board[0][0] = char('b' + rnd.next(0, 3));
        while (pathRow != n - 1 || pathCol != m - 1) {
            if (pathRow == n - 1 || (pathCol + 1 < m && rnd.next(0, 1) == 0)) {
                ++pathCol;
            } else {
                ++pathRow;
            }
            board[pathRow][pathCol] = char('a' + rnd.next(0, 2));
        }
        int distractors = rnd.next(0, n * m / 2);
        for (int k = 0; k < distractors; ++k) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            board[r][c] = min(board[r][c], char('a' + rnd.next(0, 5)));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                board[i][j] = char('a' + min(25, i + j + rnd.next(0, 2)));
            }
        }
        shuffle(board.begin(), board.end());
    } else {
        string smallAlphabet = alphabet.substr(0, rnd.next(2, 5));
        for (int i = 0; i < n; ++i) {
            board[i] = randomRow(m, smallAlphabet);
        }
        for (int d = 0; d <= n + m - 2; ++d) {
            char ch = rnd.any(smallAlphabet);
            for (int i = 0; i < n; ++i) {
                int j = d - i;
                if (0 <= j && j < m && rnd.next(0, 3) > 0) {
                    board[i][j] = ch;
                }
            }
        }
    }

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
