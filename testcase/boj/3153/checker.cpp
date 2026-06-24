#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int r, s;
vector<string> grid;

struct Answer {
    vector<string> board;
};

static const int dr[4] = {0, 1, 0, -1};
static const int dc[4] = {-1, 0, 1, 0};

static bool firesInDirection(char orientation, int dir) {
    if (orientation == '1') {
        return dir == 0 || dir == 1;
    }
    if (orientation == '2') {
        return dir == 1 || dir == 2;
    }
    if (orientation == '3') {
        return dir == 2 || dir == 3;
    }
    if (orientation == '4') {
        return dir == 3 || dir == 0;
    }
    return false;
}

static bool attackerIsHit(const vector<string>& board, int row, int col) {
    for (int dir = 0; dir < 4; ++dir) {
        int nr = row + dr[dir];
        int nc = col + dc[dir];
        while (0 <= nr && nr < r && 0 <= nc && nc < s && grid[nr][nc] != '#') {
            if (grid[nr][nc] == 'T') {
                if (firesInDirection(board[nr][nc], (dir + 2) % 4)) {
                    return true;
                }
                break;
            }
            nr += dr[dir];
            nc += dc[dir];
        }
    }
    return false;
}

static Answer readAnswer(InStream& stream) {
    Answer answer;
    for (int i = 0; i < r; ++i) {
        string row = stream.readToken(format("[Tn#.1-4]{%d}", s), format("row[%d]", i + 1));
        answer.board.push_back(row);
        for (int j = 0; j < s; ++j) {
            if (grid[i][j] == 'T') {
                if (row[j] < '1' || row[j] > '4') {
                    stream.quitf(_wa, "tower at row %d column %d is not replaced with 1..4", i + 1, j + 1);
                }
            } else if (row[j] != grid[i][j]) {
                stream.quitf(_wa,
                             "cell at row %d column %d changed from '%c' to '%c'",
                             i + 1,
                             j + 1,
                             grid[i][j],
                             row[j]);
            }
        }
        stream.readEoln();
    }
    stream.readEof();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            if (grid[i][j] != 'T') {
                continue;
            }
            for (int dir = 0; dir < 4; ++dir) {
                if (!firesInDirection(answer.board[i][j], dir)) {
                    continue;
                }
                int nr = i + dr[dir];
                int nc = j + dc[dir];
                while (0 <= nr && nr < r && 0 <= nc && nc < s && grid[nr][nc] != '#') {
                    if (grid[nr][nc] == 'T') {
                        stream.quitf(_wa,
                                     "shot from tower at row %d column %d hits tower at row %d column %d",
                                     i + 1,
                                     j + 1,
                                     nr + 1,
                                     nc + 1);
                    }
                    nr += dr[dir];
                    nc += dc[dir];
                }
            }
        }
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < s; ++j) {
            if (grid[i][j] == 'n' && !attackerIsHit(answer.board, i, j)) {
                stream.quitf(_wa, "attacker at row %d column %d is not hit", i + 1, j + 1);
            }
        }
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    r = inf.readInt(1, 100, "R");
    s = inf.readInt(1, 100, "S");
    for (int i = 0; i < r; ++i) {
        grid.push_back(inf.readToken(format("[Tn#.]{%d}", s), format("grid[%d]", i + 1)));
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid tower orientation map");
}
