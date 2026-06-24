#include "testlib.h"

#include <vector>

using namespace std;

const long long COORD_LIMIT = 1000000000000LL;
const long long DIST_LIMIT = 2000000000000000000LL;

int n, m;
vector<vector<long long>> points;

struct Answer {
    long long claimedDistance;
    long long computedDistance;
};

long long manhattanSumFor(const vector<long long>& fermatPoint, InStream& stream) {
    __int128 total = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            long long diff = points[i][j] - fermatPoint[j];
            if (diff < 0) {
                diff = -diff;
            }
            total += diff;
        }
    }
    if (total > DIST_LIMIT) {
        stream.quitf(_wa, "computed distance exceeds supported limit");
    }
    return static_cast<long long>(total);
}

Answer readAnswer(InStream& stream) {
    long long claimedDistance = stream.readLong(0, DIST_LIMIT, "total distance");
    stream.readEoln();

    vector<long long> fermatPoint(n);
    for (int j = 0; j < n; ++j) {
        if (j > 0) {
            stream.readSpace();
        }
        fermatPoint[j] = stream.readLong(-COORD_LIMIT, COORD_LIMIT,
                                         format("F[%d]", j + 1).c_str());
    }
    stream.readEoln();
    stream.readEof();

    long long computedDistance = manhattanSumFor(fermatPoint, stream);
    if (claimedDistance != computedDistance) {
        stream.quitf(_wa,
                     "claimed distance %lld does not match point distance %lld",
                     claimedDistance,
                     computedDistance);
    }

    return {claimedDistance, computedDistance};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    points.assign(m, vector<long long>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            points[i][j] = inf.readLong();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.computedDistance > jury.computedDistance) {
        quitf(_wa,
              "jury has better distance: jury=%lld participant=%lld",
              jury.computedDistance,
              participant.computedDistance);
    }
    if (participant.computedDistance < jury.computedDistance) {
        quitf(_fail,
              "participant found better distance: jury=%lld participant=%lld",
              jury.computedDistance,
              participant.computedDistance);
    }

    quitf(_ok, "distance=%lld", participant.computedDistance);
}
