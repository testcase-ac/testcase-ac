#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

void ensureBothColors(vector<string>& board) {
    bool hasW = false;
    bool hasB = false;
    for (const string& row : board) {
        hasW = hasW || row.find('W') != string::npos;
        hasB = hasB || row.find('B') != string::npos;
    }

    if (!hasW) {
        int y = rnd.next((int)board.size());
        int x = rnd.next((int)board[0].size());
        board[y][x] = 'W';
    }
    if (!hasB) {
        int y = rnd.next((int)board.size());
        int x = rnd.next((int)board[0].size());
        board[y][x] = 'B';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 18);
    int m = rnd.next(1, 18);
    if (n * m == 1) {
        if (rnd.next(2) == 0) {
            n = 2;
        } else {
            m = 2;
        }
    }

    vector<string> board(m, string(n, 'W'));
    int mode = rnd.next(5);

    if (mode == 0) {
        double whiteProb = rnd.next(0.25, 0.75);
        for (int y = 0; y < m; ++y) {
            for (int x = 0; x < n; ++x) {
                board[y][x] = rnd.next() < whiteProb ? 'W' : 'B';
            }
        }
    } else if (mode == 1) {
        bool vertical = rnd.next(2);
        int run = rnd.next(1, 4);
        for (int y = 0; y < m; ++y) {
            for (int x = 0; x < n; ++x) {
                int band = vertical ? x / run : y / run;
                board[y][x] = band % 2 == 0 ? 'W' : 'B';
            }
        }
    } else if (mode == 2) {
        for (int y = 0; y < m; ++y) {
            for (int x = 0; x < n; ++x) {
                board[y][x] = (x + y) % 2 == 0 ? 'W' : 'B';
            }
        }
    } else if (mode == 3) {
        char base = rnd.next(2) == 0 ? 'W' : 'B';
        char paint = base == 'W' ? 'B' : 'W';
        fill(board.begin(), board.end(), string(n, base));

        int rectangles = rnd.next(1, 6);
        for (int i = 0; i < rectangles; ++i) {
            int x1 = rnd.next(n);
            int x2 = rnd.next(x1, n - 1);
            int y1 = rnd.next(m);
            int y2 = rnd.next(y1, m - 1);
            for (int y = y1; y <= y2; ++y) {
                for (int x = x1; x <= x2; ++x) {
                    board[y][x] = paint;
                }
            }
            if (rnd.next(2) == 0) {
                swap(base, paint);
            }
        }
    } else {
        char common = rnd.next(2) == 0 ? 'W' : 'B';
        char rare = common == 'W' ? 'B' : 'W';
        fill(board.begin(), board.end(), string(n, common));

        int rareCells = rnd.next(1, max(1, min(n * m - 1, 8)));
        vector<int> cells(n * m);
        for (int i = 0; i < n * m; ++i) {
            cells[i] = i;
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < rareCells; ++i) {
            int cell = cells[i];
            board[cell / n][cell % n] = rare;
        }
    }

    ensureBothColors(board);

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
