#include "testlib.h"

#include <map>
#include <vector>

using namespace std;

struct Cell {
    int r;
    int c;
};

struct Answer {
    bool impossible;
};

int n;
int drainRow;
int drainCol;

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, 19000, "first output token");

    if (first == -1 && stream.seekEof()) {
        return {true};
    }

    vector<vector<int>> board(n, vector<int>(n));
    board[0][0] = first;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (r == 0 && c == 0) {
                continue;
            }
            board[r][c] = stream.readInt(-1, 19000, format("board[%d][%d]", r + 1, c + 1).c_str());
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after board");
    }

    map<int, vector<Cell>> tiles;
    int drainCount = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int value = board[r][c];
            if (value == -1) {
                ++drainCount;
                if (r != drainRow || c != drainCol) {
                    stream.quitf(_wa,
                                 "drain is at row %d column %d, expected row %d column %d",
                                 r + 1,
                                 c + 1,
                                 drainRow + 1,
                                 drainCol + 1);
                }
            } else if (value == 0) {
                stream.quitf(_wa, "tile id at row %d column %d is zero", r + 1, c + 1);
            } else {
                tiles[value].push_back({r, c});
            }
        }
    }

    if (drainCount != 1) {
        stream.quitf(_wa, "expected exactly one drain cell, found %d", drainCount);
    }

    for (const auto& entry : tiles) {
        int id = entry.first;
        const vector<Cell>& cells = entry.second;
        if (cells.size() != 3) {
            stream.quitf(_wa, "tile id %d appears %d times instead of 3", id, int(cells.size()));
        }

        int minR = cells[0].r;
        int maxR = cells[0].r;
        int minC = cells[0].c;
        int maxC = cells[0].c;
        for (const Cell& cell : cells) {
            minR = min(minR, cell.r);
            maxR = max(maxR, cell.r);
            minC = min(minC, cell.c);
            maxC = max(maxC, cell.c);
        }
        if (maxR - minR > 1 || maxC - minC > 1) {
            stream.quitf(_wa, "tile id %d does not fit inside one 2x2 block", id);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int k = inf.readInt();
    n = 1 << k;
    int x = inf.readInt();
    int y = inf.readInt();

    drainRow = n - y;
    drainCol = x - 1;

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid tiling but jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible but jury provides a tiling");
    }

    quitf(_ok, "valid tiling");
}
