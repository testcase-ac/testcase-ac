#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int l = inf.readInt(2, 1000000000, "l");
    inf.readEoln();

    set<int> positions;
    vector<int> fallTimes;
    fallTimes.reserve(n);

    for (int i = 1; i <= n; ++i) {
        int signedPosition = inf.readInt(-(l - 1), l - 1, "x_i");
        inf.readEoln();

        ensuref(signedPosition != 0, "ant %d has zero position", i);

        int position = abs(signedPosition);
        ensuref(positions.insert(position).second,
                "duplicate ant position at ant %d: %d", i, position);

        if (signedPosition > 0) {
            fallTimes.push_back(l - position);
        } else {
            fallTimes.push_back(position);
        }
    }

    int lastFallTime = *max_element(fallTimes.begin(), fallTimes.end());
    int lastFallCount = count(fallTimes.begin(), fallTimes.end(), lastFallTime);
    ensuref(lastFallCount == 1,
            "multiple ants fall last at time %d", lastFallTime);

    inf.readEof();
}
