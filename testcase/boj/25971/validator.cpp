#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

struct Observation {
    int day;
    long long x;
    long long y;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(3, n, "K");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "R");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    vector<Observation> observations;
    observations.reserve(k);
    for (int idx = 1; idx <= k; ++idx) {
        int day = inf.readInt(1, n, "i");
        inf.readSpace();
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();

        if (!observations.empty()) {
            ensuref(observations.back().day < day,
                    "observation days must be strictly increasing: %d then %d",
                    observations.back().day,
                    day);

            const Observation& prev = observations.back();
            long long dx = llabs(x - prev.x);
            long long dy = llabs(y - prev.y);
            long long dt = day - prev.day;
            ensuref((dx == dt && dy == 0) || (dx == 0 && dy == dt),
                    "observations %d and %d are not reachable by axis-parallel speed-1 movement",
                    idx - 1,
                    idx);
        }

        observations.push_back({day, x, y});
    }

    ensuref(observations.front().day == 1,
            "first observation day must be 1, found %d",
            observations.front().day);
    ensuref(observations.back().day == n,
            "last observation day must be N=%d, found %d",
            n,
            observations.back().day);

    for (int idx = 1; idx <= q; ++idx) {
        inf.readInt(1, n, "j");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "x_j");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "y_j");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
