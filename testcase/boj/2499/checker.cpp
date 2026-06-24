#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int n;
vector<vector<int> > rice;
long long totalRice;

struct Claim {
    long long diff;
    vector<int> lowerCells;
};

Claim readClaim(InStream& stream) {
    long long claimedDiff = stream.readLong(0, totalRice, "claimed difference");
    stream.readEoln();

    vector<int> lowerCells(n);
    for (int col = 0; col < n; ++col) {
        lowerCells[col] = stream.readInt(0, n, format("lowerCells[%d]", col + 1).c_str());
        if (col > 0 && lowerCells[col] < lowerCells[col - 1]) {
            stream.quitf(_wa,
                         "lowerCells[%d]=%d is smaller than lowerCells[%d]=%d",
                         col + 1,
                         lowerCells[col],
                         col,
                         lowerCells[col - 1]);
        }
    }
    stream.readEoln();
    stream.readEof();

    long long brotherRice = 0;
    for (int col = 0; col < n; ++col) {
        for (int row = n - lowerCells[col]; row < n; ++row) {
            brotherRice += rice[row][col];
        }
    }

    long long actualDiff = llabs(totalRice - 2 * brotherRice);
    if (actualDiff != claimedDiff) {
        stream.quitf(_wa,
                     "claimed difference %lld does not match allocation difference %lld",
                     claimedDiff,
                     actualDiff);
    }

    return {actualDiff, lowerCells};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 20, "N");
    rice.assign(n, vector<int>(n));
    totalRice = 0;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            rice[row][col] = inf.readInt(0, 100, format("rice[%d][%d]", row + 1, col + 1).c_str());
            totalRice += rice[row][col];
        }
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.diff > jury.diff) {
        quitf(_wa,
              "participant difference %lld is worse than jury difference %lld",
              participant.diff,
              jury.diff);
    }
    if (participant.diff < jury.diff) {
        quitf(_fail,
              "participant found a better difference: participant=%lld jury=%lld",
              participant.diff,
              jury.diff);
    }

    quitf(_ok, "difference %lld", participant.diff);
}
