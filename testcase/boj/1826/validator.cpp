#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    set<int> positions;
    vector<int> stationPositions;
    stationPositions.reserve(n);
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(1, 1000000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 100, "b");
        inf.readEoln();

        ensuref(positions.insert(a).second,
                "station position must be unique at line %d: %d", i + 2, a);
        stationPositions.push_back(a);
    }

    int l = inf.readInt(1, 1000000, "L");
    inf.readSpace();
    int p = inf.readInt(1, 1000000, "P");
    inf.readEoln();

    ensuref(positions.insert(l).second,
            "town position must differ from all station positions: %d", l);
    for (int i = 0; i < n; ++i) {
        ensuref(stationPositions[i] < l,
                "station %d must be left of the town: station=%d town=%d",
                i + 1, stationPositions[i], l);
    }

    inf.readEof();
}
