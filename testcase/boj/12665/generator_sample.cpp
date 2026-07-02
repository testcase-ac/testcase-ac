#include "testlib.h"
#include <vector>
using namespace std;

vector<vector<int>> makeMines(int rows, int cols, int mode) {
    vector<vector<int>> mines(rows, vector<int>(cols, 0));

    if (mode == 0) {
        return mines;
    }

    if (mode == 1) {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                mines[row][col] = 1;
            }
        }
        return mines;
    }

    if (mode == 2) {
        int middle = rows / 2;
        for (int col = 0; col < cols; ++col) {
            mines[middle][col] = rnd.next(0, 1);
        }
        return mines;
    }

    if (mode == 3) {
        int parity = rnd.next(0, 1);
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                mines[row][col] = ((row + col) % 2 == parity);
            }
        }
        return mines;
    }

    int threshold = (mode == 4 ? rnd.next(15, 35) : rnd.next(45, 80));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            mines[row][col] = (rnd.next(1, 100) <= threshold);
        }
    }
    return mines;
}

vector<vector<int>> makeClues(const vector<vector<int>>& mines) {
    int rows = (int)mines.size();
    int cols = (int)mines[0].size();
    vector<vector<int>> clues(rows, vector<int>(cols, 0));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            for (int dr = -1; dr <= 1; ++dr) {
                int nr = row + dr;
                if (nr < 0 || nr >= rows) continue;
                for (int dc = -1; dc <= 1; ++dc) {
                    int nc = col + dc;
                    if (nc < 0 || nc >= cols) continue;
                    clues[row][col] += mines[nr][nc];
                }
            }
        }
    }
    return clues;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(1, 8);
    println(tests);

    for (int test = 0; test < tests; ++test) {
        int rows = rnd.next(0, 1) == 0 ? 3 : 5;
        int cols = rnd.next(3, 5);
        int mode = rnd.next(0, 5);
        vector<vector<int>> clues = makeClues(makeMines(rows, cols, mode));

        println(rows, cols);
        for (int row = 0; row < rows; ++row) {
            println(clues[row]);
        }
    }

    return 0;
}
