#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void fillRandom(vector<string>& board, double probability) {
    for (string& row : board) {
        for (char& cell : row) {
            cell = rnd.next() < probability ? '1' : '0';
        }
    }
}

void addRectangle(vector<string>& board, int top, int left, int height, int width) {
    for (int r = top; r < top + height; ++r) {
        for (int c = left; c < left + width; ++c) {
            board[r][c] = '1';
        }
    }
}

void addLShape(vector<string>& board) {
    int n = board.size();
    int m = board[0].size();
    if (n < 3 || m < 2) return;

    int totalHeight = rnd.next(3, n);
    int lowerHeight = rnd.next(1, (totalHeight - 1) / 2);
    int upperHeight = totalHeight - lowerHeight;

    int upperWidth = rnd.next(1, max(1, m - 1));
    int lowerWidth = rnd.next(upperWidth + 1, m);

    int top = rnd.next(0, n - totalHeight);
    int left = rnd.next(0, m - lowerWidth);

    addRectangle(board, top, left, upperHeight, upperWidth);
    addRectangle(board, top + upperHeight, left, lowerHeight, lowerWidth);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
    } else if (mode == 5) {
        n = rnd.next(20, 35);
        m = rnd.next(20, 35);
    } else {
        n = rnd.next(6, 18);
        m = rnd.next(6, 18);
    }

    vector<string> board(n, string(m, '0'));

    if (mode == 0) {
        vector<double> probabilities = {0.0, 0.25, 0.5, 0.75, 1.0};
        fillRandom(board, probabilities[rnd.next(static_cast<int>(probabilities.size()))]);
    } else if (mode == 1) {
        fillRandom(board, rnd.next(0.05, 0.35));
    } else if (mode == 2) {
        fillRandom(board, rnd.next(0.65, 0.95));
    } else if (mode == 3) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                bool vertical = c % rnd.next(2, 5) == 0;
                bool horizontal = r % rnd.next(2, 5) == 0;
                board[r][c] = (vertical || horizontal || rnd.next() < 0.15) ? '1' : '0';
            }
        }
    } else {
        fillRandom(board, rnd.next(0.0, 0.2));
        int shapes = rnd.next(1, 4);
        for (int i = 0; i < shapes; ++i) addLShape(board);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next() < 0.03) board[r][c] = '0';
            }
        }
    }

    println(n, m);
    for (const string& row : board) println(row);

    return 0;
}
