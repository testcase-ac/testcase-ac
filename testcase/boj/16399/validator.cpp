#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 500, "C");
    inf.readSpace();
    int e = inf.readInt(1, 500, "E");
    inf.readSpace();
    int d = inf.readInt(1, 10000, "D");
    inf.readEoln();

    int n = inf.readInt(0, 1000, "N");
    inf.readEoln();

    if (n > 0) {
        vector<int> s = inf.readInts(n, 1, 10000, "S_i");
        inf.readEoln();

        vector<int> p = inf.readInts(n, 1, 10000, "P_i");
        inf.readEoln();

        long long stationDistance = 0;
        for (int i = 0; i < n; ++i) {
            stationDistance += s[i];
        }

        // CHECK: The statement describes the stations as lying between home and the destination,
        // so the cumulative station segment distance must not pass D.
        ensuref(stationDistance <= d,
                "sum of station segment distances exceeds D: %lld > %d",
                stationDistance,
                d);
    }

    inf.readEof();
}
