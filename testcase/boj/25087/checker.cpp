#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

struct CaseInput {
    int rows;
    int cols;
    vector<string> blocks;
};

struct Claim {
    bool impossible;
};

void readCasePrefix(InStream& stream, int expectedCase) {
    string token = stream.readToken();
    string expected = "Case #" + toString(expectedCase) + ":";
    if (token == expected) {
        return;
    }

    if (token == "Case") {
        string number = stream.readToken();
        string expectedNumber = "#" + toString(expectedCase) + ":";
        if (number == expectedNumber) {
            return;
        }
        stream.quitf(_wa, "Case #%d: expected prefix \"%s\", found \"Case %s\"",
                     expectedCase, expected.c_str(), number.c_str());
    }

    stream.quitf(_wa, "Case #%d: expected prefix \"%s\", found \"%s\"",
                 expectedCase, expected.c_str(), token.c_str());
}

int moveRow(char direction) {
    if (direction == 'N') return -1;
    if (direction == 'S') return 1;
    return 0;
}

int moveCol(char direction) {
    if (direction == 'W') return -1;
    if (direction == 'E') return 1;
    return 0;
}

Claim readClaim(InStream& stream, const CaseInput& input, int caseIndex) {
    readCasePrefix(stream, caseIndex);
    string answer = stream.readToken();

    if (answer == "IMPOSSIBLE") {
        return {true};
    }

    int height = input.rows * 2;
    int width = input.cols * 2;
    vector<vector<int> > empty(height, vector<int>(width, 0));
    int emptyCount = 0;
    for (int r = 0; r < input.rows; ++r) {
        for (int c = 0; c < input.cols; ++c) {
            if (input.blocks[r][c] == '*') {
                for (int dr = 0; dr < 2; ++dr) {
                    for (int dc = 0; dc < 2; ++dc) {
                        empty[2 * r + dr][2 * c + dc] = 1;
                        ++emptyCount;
                    }
                }
            }
        }
    }

    if (int(answer.size()) != emptyCount) {
        stream.quitf(_wa, "Case #%d: route length is %d, expected %d",
                     caseIndex, int(answer.size()), emptyCount);
    }

    vector<vector<int> > seen(height, vector<int>(width, 0));
    int row = 0;
    int col = 0;
    seen[row][col] = 1;
    int visited = 1;

    for (int i = 0; i < int(answer.size()); ++i) {
        char direction = answer[i];
        if (direction != 'N' && direction != 'E' && direction != 'S' && direction != 'W') {
            stream.quitf(_wa, "Case #%d: invalid move '%c' at position %d",
                         caseIndex, direction, i + 1);
        }

        row += moveRow(direction);
        col += moveCol(direction);
        if (row < 0 || row >= height || col < 0 || col >= width) {
            stream.quitf(_wa, "Case #%d: move %d leaves the grid",
                         caseIndex, i + 1);
        }
        if (!empty[row][col]) {
            stream.quitf(_wa, "Case #%d: move %d enters a building cell",
                         caseIndex, i + 1);
        }

        bool lastMove = (i + 1 == int(answer.size()));
        if (lastMove) {
            if (row != 0 || col != 0) {
                stream.quitf(_wa, "Case #%d: final position is A_%d,%d instead of A_1,1",
                             caseIndex, row + 1, col + 1);
            }
        } else {
            if (seen[row][col]) {
                stream.quitf(_wa, "Case #%d: cell A_%d,%d is visited more than once",
                             caseIndex, row + 1, col + 1);
            }
            seen[row][col] = 1;
            ++visited;
        }
    }

    if (visited != emptyCount) {
        stream.quitf(_wa, "Case #%d: visited %d empty cells, expected %d",
                     caseIndex, visited, emptyCount);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    vector<CaseInput> inputs(tests);
    for (int caseIndex = 0; caseIndex < tests; ++caseIndex) {
        CaseInput current;
        current.rows = inf.readInt();
        current.cols = inf.readInt();
        current.blocks.resize(current.rows);
        for (int r = 0; r < current.rows; ++r) {
            current.blocks[r] = inf.readToken();
        }
        inputs[caseIndex] = current;
    }

    for (int caseIndex = 1; caseIndex <= tests; ++caseIndex) {
        Claim jury = readClaim(ans, inputs[caseIndex - 1], caseIndex);
        Claim participant = readClaim(ouf, inputs[caseIndex - 1], caseIndex);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "Case #%d: participant found a valid route while jury says IMPOSSIBLE",
                  caseIndex);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "Case #%d: jury has a valid route but participant says IMPOSSIBLE",
                  caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "%d case(s) passed", tests);
}
