#include "testlib.h"
#include <vector>
using namespace std;

struct Claim {
    bool impossible;
};

int h;
vector<int> w;
long long needOnes, needNines;

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, 9, "first token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<long long> rowSum(h, 0);
    long long ones = 0;
    long long nines = 0;

    auto consumeTile = [&](int row, int col, int value) {
        if (value != 1 && value != 9) {
            stream.quitf(_wa, "tile at row %d column %d is %d, expected 1 or 9",
                         row + 1, col + 1, value);
        }
        rowSum[row] += value;
        if (value == 1) {
            ++ones;
        } else {
            ++nines;
        }
    };

    consumeTile(0, 0, first);
    for (int row = 0; row < h; ++row) {
        int start = (row == 0 ? 1 : 0);
        for (int col = start; col < w[row]; ++col) {
            int value = stream.readInt(1, 9, format("tile[%d][%d]", row + 1, col + 1).c_str());
            consumeTile(row, col, value);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after construction");
    }
    if (ones != needOnes || nines != needNines) {
        stream.quitf(_wa, "used %lld ones and %lld nines, expected %lld ones and %lld nines",
                     ones, nines, needOnes, needNines);
    }
    for (int row = 1; row < h; ++row) {
        if (rowSum[row - 1] >= rowSum[row]) {
            stream.quitf(_wa, "row sums are not strictly increasing at rows %d and %d: %lld >= %lld",
                         row, row + 1, rowSum[row - 1], rowSum[row]);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    h = inf.readInt();
    w.resize(h);
    for (int i = 0; i < h; ++i) {
        w[i] = inf.readInt();
    }
    needOnes = inf.readLong();
    needNines = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "participant claims impossible but jury provides a valid construction");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant provides a valid construction while jury claims impossible");
    }
    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs claim impossible");
    }

    quitf(_ok, "valid construction");
}
