#include "testlib.h"

#include <map>
#include <vector>

using namespace std;

int k;
int side;
int drainX;
int drainY;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    vector<int> values;
    while (!stream.seekEof()) {
        values.push_back(stream.readInt(-1, 19000, "cell"));
    }

    if (values.size() == 1 && values[0] == -1) {
        return {true};
    }

    int expectedCells = side * side;
    if ((int)values.size() != expectedCells) {
        stream.quitf(_wa, "expected %d grid values, found %d", expectedCells, (int)values.size());
    }

    int drainRow = side - drainY;
    int drainCol = drainX - 1;
    map<int, vector<pair<int, int>>> cellsByTile;

    for (int row = 0; row < side; ++row) {
        for (int col = 0; col < side; ++col) {
            int value = values[row * side + col];
            if (row == drainRow && col == drainCol) {
                if (value != -1) {
                    stream.quitf(_wa, "drain cell (%d,%d) must be -1, found %d", drainX, drainY, value);
                }
                continue;
            }

            if (value == -1) {
                int x = col + 1;
                int y = side - row;
                stream.quitf(_wa, "non-drain cell (%d,%d) is -1", x, y);
            }
            if (value < 1) {
                stream.quitf(_wa, "tile number must be positive, found %d", value);
            }
            cellsByTile[value].push_back({row, col});
        }
    }

    int expectedTiles = (side * side - 1) / 3;
    if ((int)cellsByTile.size() != expectedTiles) {
        stream.quitf(_wa, "expected %d tile ids, found %d", expectedTiles, (int)cellsByTile.size());
    }

    for (const auto& [id, cells] : cellsByTile) {
        if ((int)cells.size() != 3) {
            stream.quitf(_wa, "tile %d covers %d cells instead of 3", id, (int)cells.size());
        }

        int minRow = cells[0].first;
        int maxRow = cells[0].first;
        int minCol = cells[0].second;
        int maxCol = cells[0].second;
        for (const auto& [row, col] : cells) {
            minRow = min(minRow, row);
            maxRow = max(maxRow, row);
            minCol = min(minCol, col);
            maxCol = max(maxCol, col);
        }

        if (maxRow - minRow != 1 || maxCol - minCol != 1) {
            stream.quitf(_wa, "tile %d is not contained in a 2x2 block", id);
        }

        bool used[2][2] = {};
        for (const auto& [row, col] : cells) {
            used[row - minRow][col - minCol] = true;
        }

        int usedCount = 0;
        for (int row = 0; row < 2; ++row) {
            for (int col = 0; col < 2; ++col) {
                if (used[row][col]) {
                    ++usedCount;
                }
            }
        }
        if (usedCount != 3) {
            stream.quitf(_wa, "tile %d does not form an L-tromino", id);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    k = inf.readInt();
    side = 1 << k;
    drainX = inf.readInt();
    drainY = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report no tiling");
        }
        quitf(_fail, "participant provided a valid tiling while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports no tiling, but jury has a valid tiling");
    }

    quitf(_ok, "valid tiling");
}
