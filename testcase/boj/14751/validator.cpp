#include "testlib.h"
#include <string>
#include <unordered_set>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the y-coordinates of the upper and lower horizontal lines
    int maxY = inf.readInt(-1000, 1000, "maxY");
    inf.readSpace();
    int minY = inf.readInt(-1000, 1000, "minY");
    ensuref(minY < maxY,
            "minY (%d) must be strictly less than maxY (%d)", minY, maxY);
    inf.readEoln();

    // Number of segments
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read segments, ensuring endpoints on each line are distinct
    unordered_set<int> upperXs;
    unordered_set<int> lowerXs;
    upperXs.reserve(n);
    lowerXs.reserve(n);

    for (int i = 0; i < n; i++) {
        int ux = inf.readInt(-500000, 500000, "upperX");
        inf.readSpace();
        int lx = inf.readInt(-500000, 500000, "lowX");
        inf.readEoln();
        ensuref(!upperXs.count(ux),
                "Duplicate upper endpoint x at segment %d: %d", i+1, ux);
        ensuref(!lowerXs.count(lx),
                "Duplicate lower endpoint x at segment %d: %d", i+1, lx);
        upperXs.insert(ux);
        lowerXs.insert(lx);
    }

    // Number of queries
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Read each query y-coordinate: real number with 1–3 decimal digits, strictly between minY and maxY
    for (int i = 0; i < m; i++) {
        // Regex: optional '-', digits+, '.', 1 to 3 digits
        string qs = inf.readToken("-?[0-9]+\\.[0-9]{1,3}", "q_y");
        inf.readEoln();
        // Parse and check bounds
        long double y = stold(qs);
        ensuref(y > minY,
                "Query %d: y = %s is not strictly greater than minY = %d", i+1, qs.c_str(), minY);
        ensuref(y < maxY,
                "Query %d: y = %s is not strictly less than maxY = %d", i+1, qs.c_str(), maxY);
    }

    inf.readEof();
    return 0;
}
