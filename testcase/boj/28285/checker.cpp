#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int n, startRow, startCol;
int totalRooms;
vector<int> rowStart;

struct Answer {
    bool impossible;
};

int rowLength(int row) {
    return 2 * n - 1 - abs(row - n);
}

bool inside(int row, int col) {
    return 1 <= row && row <= 2 * n - 1 && 1 <= col && col <= rowLength(row);
}

int roomId(int row, int col) {
    return rowStart[row] + col - 1;
}

void moveRoom(char direction, int& row, int& col) {
    switch (direction) {
        case 'Q':
            if (row <= n) {
                --row;
                --col;
            } else {
                --row;
            }
            break;
        case 'E':
            if (row <= n) {
                --row;
            } else {
                --row;
                ++col;
            }
            break;
        case 'D':
            ++col;
            break;
        case 'C':
            if (row < n) {
                ++row;
                ++col;
            } else {
                ++row;
            }
            break;
        case 'Z':
            if (row < n) {
                ++row;
            } else {
                ++row;
                --col;
            }
            break;
        case 'A':
            --col;
            break;
        default:
            break;
    }
}

Answer readAnswer(InStream& stream) {
    string token = stream.readToken();
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (token == "-1") {
        return {true};
    }

    if ((int)token.size() != totalRooms) {
        stream.quitf(_wa, "path length is %d, expected %d", (int)token.size(), totalRooms);
    }

    vector<char> visited(totalRooms, 0);
    int row = startRow;
    int col = startCol;
    const int startId = roomId(row, col);
    visited[startId] = 1;

    for (int i = 0; i < totalRooms; ++i) {
        char direction = token[i];
        if (direction != 'Q' && direction != 'E' && direction != 'D' &&
            direction != 'C' && direction != 'Z' && direction != 'A') {
            stream.quitf(_wa, "invalid direction '%c' at move %d", direction, i + 1);
        }

        moveRoom(direction, row, col);
        if (!inside(row, col)) {
            stream.quitf(_wa, "move %d leaves the hexagon at (%d, %d)", i + 1, row, col);
        }

        int id = roomId(row, col);
        if (i + 1 == totalRooms) {
            if (id != startId) {
                stream.quitf(_wa,
                             "final move ends at (%d, %d), expected start (%d, %d)",
                             row,
                             col,
                             startRow,
                             startCol);
            }
        } else {
            if (visited[id]) {
                stream.quitf(_wa, "room (%d, %d) is visited more than once", row, col);
            }
            visited[id] = 1;
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 1000, "N");
    startRow = inf.readInt(1, 2 * n - 1, "x");
    startCol = inf.readInt(1, rowLength(startRow), "y");

    rowStart.assign(2 * n, 0);
    totalRooms = 0;
    for (int row = 1; row <= 2 * n - 1; ++row) {
        rowStart[row] = totalRooms;
        totalRooms += rowLength(row);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid cycle while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a valid cycle");
    }

    quitf(_ok, "valid Hamiltonian cycle");
}
