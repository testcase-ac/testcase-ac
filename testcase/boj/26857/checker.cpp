#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    int rows;
    int cols;
    long long area;
};

int inputRows, inputCols;
array<int, 26> inputCount;

Claim readClaim(InStream& stream) {
    int rows = stream.readInt(inputRows, 1000000, "R'");
    int cols = stream.readInt(inputCols, 1000000, "C'");
    stream.readEoln();

    vector<string> board(rows);
    array<int, 26> outputCount{};
    array<int, 26> colorParity;
    colorParity.fill(-1);

    for (int r = 0; r < rows; ++r) {
        board[r] = stream.readToken("[.a-z]+", format("row[%d]", r + 1).c_str());
        if ((int)board[r].size() != cols) {
            stream.quitf(_wa, "row %d has length %d instead of %d", r + 1, (int)board[r].size(), cols);
        }
        stream.readEoln();

        for (int c = 0; c < cols; ++c) {
            char ch = board[r][c];
            if (ch == '.') {
                continue;
            }
            if (ch < 'a' || ch > 'z') {
                stream.quitf(_wa, "invalid character '%c' at row %d column %d", ch, r + 1, c + 1);
            }

            int id = ch - 'a';
            ++outputCount[id];
            int parity = (r + c) & 1;
            if (colorParity[id] == -1) {
                colorParity[id] = parity;
            } else if (colorParity[id] != parity) {
                stream.quitf(_wa, "color %c appears on both chessboard parities", ch);
            }
        }
    }
    stream.readEof();

    for (int i = 0; i < 26; ++i) {
        if (outputCount[i] != inputCount[i]) {
            stream.quitf(_wa,
                         "color %c count is %d instead of %d",
                         char('a' + i),
                         outputCount[i],
                         inputCount[i]);
        }
    }

    return {rows, cols, 1LL * rows * cols};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    inputRows = inf.readInt();
    inputCols = inf.readInt();
    inputCount.fill(0);
    for (int r = 0; r < inputRows; ++r) {
        string row = inf.readToken();
        for (char ch : row) {
            if (ch >= 'a' && ch <= 'z') {
                ++inputCount[ch - 'a'];
            }
        }
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.area > jury.area) {
        quitf(_wa,
              "participant board area %lld is larger than jury area %lld",
              participant.area,
              jury.area);
    }
    if (participant.area < jury.area) {
        quitf(_fail,
              "participant found smaller valid board area: participant=%lld jury=%lld",
              participant.area,
              jury.area);
    }

    quitf(_ok, "valid board with minimum area %lld", participant.area);
}
