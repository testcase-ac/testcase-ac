#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int H, W, C, D;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    string first = stream.readToken();

    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<long long> rowSums(H, 0);
    int count1 = 0;
    int count9 = 0;

    auto consumeTile = [&](int row, int col, const string& token) {
        if (token == "1") {
            ++count1;
            rowSums[row] += 1;
            return;
        }
        if (token == "9") {
            ++count9;
            rowSums[row] += 9;
            return;
        }
        stream.quitf(_wa,
                     "cell[%d][%d] must be 1 or 9, found '%s'",
                     row + 1,
                     col + 1,
                     token.c_str());
    };

    consumeTile(0, 0, first);
    for (int row = 0; row < H; ++row) {
        int startCol = (row == 0 ? 1 : 0);
        for (int col = startCol; col < W; ++col) {
            string token = stream.readToken();
            consumeTile(row, col, token);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after construction");
    }

    if (count1 != C) {
        stream.quitf(_wa, "expected %d tiles of 1, found %d", C, count1);
    }
    if (count9 != D) {
        stream.quitf(_wa, "expected %d tiles of 9, found %d", D, count9);
    }
    for (int row = 1; row < H; ++row) {
        if (rowSums[row - 1] >= rowSums[row]) {
            stream.quitf(_wa,
                         "row sums must be strictly increasing, but row %d has %lld and row %d has %lld",
                         row,
                         rowSums[row - 1],
                         row + 1,
                         rowSums[row]);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    H = inf.readInt();
    W = inf.readInt();
    C = inf.readInt();
    D = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "jury claims impossible, but participant output is a valid construction");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible, but jury provides a valid construction");
    }

    quitf(_ok, "valid construction");
}
