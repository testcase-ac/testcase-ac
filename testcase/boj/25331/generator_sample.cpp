#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const int N = 7;

bool hasPendingRemoval(const vector<vector<int>>& board) {
    vector<vector<bool>> marked(N, vector<bool>(N, false));

    for (int r = 0; r < N; ++r) {
        int c = 0;
        while (c < N) {
            if (board[r][c] == 0) {
                ++c;
                continue;
            }
            int start = c;
            while (c < N && board[r][c] != 0) {
                ++c;
            }
            int len = c - start;
            for (int j = start; j < c; ++j) {
                if (board[r][j] == len) {
                    marked[r][j] = true;
                }
            }
        }
    }

    for (int c = 0; c < N; ++c) {
        int r = 0;
        while (r < N) {
            if (board[r][c] == 0) {
                ++r;
                continue;
            }
            int start = r;
            while (r < N && board[r][c] != 0) {
                ++r;
            }
            int len = r - start;
            for (int i = start; i < r; ++i) {
                if (board[i][c] == len) {
                    marked[i][c] = true;
                }
            }
        }
    }

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (marked[r][c]) {
                return true;
            }
        }
    }
    return false;
}

vector<int> chooseHeights(int mode) {
    vector<int> heights(N, 0);

    if (mode == 0) {
        return heights;
    }
    if (mode == 1) {
        for (int& h : heights) {
            h = rnd.next(0, 2);
        }
        return heights;
    }
    if (mode == 2) {
        for (int& h : heights) {
            h = rnd.next(0, 4);
        }
        return heights;
    }
    if (mode == 3) {
        for (int& h : heights) {
            h = rnd.next(3, 6);
        }
        return heights;
    }
    if (mode == 4) {
        for (int c = 0; c < N; ++c) {
            heights[c] = min(6, c + rnd.next(0, 2));
        }
        shuffle(heights.begin(), heights.end());
        return heights;
    }

    int first = rnd.next(0, N - 1);
    int second = rnd.next(0, N - 1);
    while (second == first) {
        second = rnd.next(0, N - 1);
    }
    heights[first] = rnd.next(4, 6);
    heights[second] = rnd.next(4, 6);
    for (int c = 0; c < N; ++c) {
        if (c != first && c != second) {
            heights[c] = rnd.next(0, 2);
        }
    }
    return heights;
}

vector<vector<int>> buildBoard(const vector<int>& heights) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    for (int c = 0; c < N; ++c) {
        for (int k = 0; k < heights[c]; ++k) {
            board[N - 1 - k][c] = rnd.next(1, 7);
        }
    }
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<int>> board(N, vector<int>(N, 0));
    for (int attempt = 0; attempt < 10000; ++attempt) {
        int mode = rnd.next(0, 5);
        vector<int> heights = chooseHeights(mode);
        vector<vector<int>> candidate = buildBoard(heights);
        if (!hasPendingRemoval(candidate)) {
            board = candidate;
            break;
        }
    }

    for (const auto& row : board) {
        println(row);
    }
    println(rnd.next(1, 7));

    return 0;
}
