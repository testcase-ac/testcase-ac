#include "testlib.h"

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int h, w, c;
vector<int> requiredCount;
long long upperBound;

struct Answer {
    long long score;
};

void dropAndCompact(vector<vector<int>>& board) {
    vector<vector<int>> columns;

    for (int col = 0; col < w; ++col) {
        vector<int> kept;
        for (int row = h - 1; row >= 0; --row) {
            if (board[row][col] != 0) {
                kept.push_back(board[row][col]);
            }
        }
        if (!kept.empty()) {
            columns.push_back(kept);
        }
    }

    board.assign(h, vector<int>(w, 0));
    for (int col = 0; col < (int)columns.size(); ++col) {
        for (int i = 0; i < (int)columns[col].size(); ++i) {
            board[h - 1 - i][col] = columns[col][i];
        }
    }
}

bool colorIsConnected(const vector<vector<int>>& board, int color) {
    int total = 0;
    int startRow = -1;
    int startCol = -1;

    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            if (board[row][col] == color) {
                ++total;
                startRow = row;
                startCol = col;
            }
        }
    }

    if (total == 0) {
        return false;
    }

    vector<vector<int>> seen(h, vector<int>(w, 0));
    queue<pair<int, int>> q;
    q.push({startRow, startCol});
    seen[startRow][startCol] = 1;

    int reached = 0;
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        ++reached;

        for (int dir = 0; dir < 4; ++dir) {
            int nr = row + dr[dir];
            int nc = col + dc[dir];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                continue;
            }
            if (!seen[nr][nc] && board[nr][nc] == color) {
                seen[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }

    return reached == total;
}

void removeColor(vector<vector<int>>& board, int color) {
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            if (board[row][col] == color) {
                board[row][col] = 0;
            }
        }
    }
    dropAndCompact(board);
}

bool canReachUpperBound(const vector<vector<int>>& initialBoard) {
    vector<int> order(c);
    for (int i = 0; i < c; ++i) {
        order[i] = i + 1;
    }

    do {
        vector<vector<int>> board = initialBoard;
        bool ok = true;
        for (int color : order) {
            if (!colorIsConnected(board, color)) {
                ok = false;
                break;
            }
            removeColor(board, color);
        }
        if (ok) {
            return true;
        }
    } while (next_permutation(order.begin(), order.end()));

    return false;
}

Answer readAnswer(InStream& stream) {
    vector<vector<int>> board(h, vector<int>(w));
    vector<int> seenCount(c + 1, 0);

    for (int row = 0; row < h; ++row) {
        string line = stream.readToken(format("[1-%d]{%d}", c, w).c_str(),
                                       format("row[%d]", row + 1).c_str());
        for (int col = 0; col < w; ++col) {
            int color = line[col] - '0';
            board[row][col] = color;
            ++seenCount[color];
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after board");
    }

    for (int color = 1; color <= c; ++color) {
        if (seenCount[color] != requiredCount[color]) {
            stream.quitf(_wa,
                         "color %d appears %d times, expected %d",
                         color,
                         seenCount[color],
                         requiredCount[color]);
        }
    }

    if (!canReachUpperBound(board)) {
        return {upperBound - 1};
    }
    return {upperBound};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    h = inf.readInt();
    w = inf.readInt();
    c = inf.readInt();

    requiredCount.assign(c + 1, 0);
    for (int color = 1; color <= c; ++color) {
        requiredCount[color] = inf.readInt();
    }
    upperBound = 0;
    for (int color = 1; color <= c; ++color) {
        upperBound += 1LL * requiredCount[color] * requiredCount[color];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.score < upperBound) {
        quitf(_fail, "jury board cannot reach the upper bound score %lld", upperBound);
    }
    if (participant.score < jury.score) {
        quitf(_wa,
              "jury has better board: jury=%lld participant=%lld",
              jury.score,
              participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail,
              "participant found better board: jury=%lld participant=%lld",
              jury.score,
              participant.score);
    }
    quitf(_ok, "score=%lld", participant.score);
}
