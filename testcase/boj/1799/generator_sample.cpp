#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int n = rnd.next(1, 10);
    const int mode = rnd.next(0, 5);
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (mode == 0) {
        const int threshold = rnd.next(15, 85);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                board[r][c] = rnd.next(100) < threshold;
            }
        }
    } else if (mode == 1) {
        const int keepColor = rnd.next(0, 1);
        const int threshold = rnd.next(35, 90);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if ((r + c) % 2 == keepColor || rnd.next(100) < 15) {
                    board[r][c] = rnd.next(100) < threshold;
                }
            }
        }
    } else if (mode == 2) {
        const int mainShift = rnd.next(-(n - 1), n - 1);
        const int antiSum = rnd.next(0, 2 * (n - 1));
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r - c == mainShift || r + c == antiSum || rnd.next(100) < 20) {
                    board[r][c] = 1;
                }
            }
        }
    } else if (mode == 3) {
        const int blockSize = rnd.next(1, n);
        const int top = rnd.next(0, n - blockSize);
        const int left = rnd.next(0, n - blockSize);
        for (int r = top; r < top + blockSize; ++r) {
            for (int c = left; c < left + blockSize; ++c) {
                board[r][c] = rnd.next(100) < 80;
            }
        }
    } else {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                board[r][c] = 1;
            }
        }
        const int holes = rnd.next(0, n * n / 2);
        for (int i = 0; i < holes; ++i) {
            board[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = 0;
        }
    }

    println(n);
    for (int r = 0; r < n; ++r) {
        println(board[r]);
    }

    return 0;
}
