#include "testlib.h"

#include <cmath>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (!inf.seekEof()) {
        ++caseCount;
        // CHECK: The statement gives EOF-terminated cases with no case-count limit.
        ensuref(caseCount <= 20000, "too many cases: %d", caseCount);
        setTestCase(caseCount);

        int n = inf.readInt(1, 99, "n");
        inf.readSpace();
        int m = inf.readInt(1, 99, "m");
        inf.readSpace();
        int s = inf.readInt(1, 99, "s");
        inf.readSpace();
        int v = inf.readInt(1, 99, "v");
        inf.readEoln();

        set<pair<double, double>> points;
        for (int i = 0; i < n + m; ++i) {
            // CHECK: The statement omits coordinate bounds; this finite metre-scale cap
            // keeps inputs practical while preserving the problem's geometry.
            double x = inf.readDouble(-1e9, 1e9, "x");
            inf.readSpace();
            double y = inf.readDouble(-1e9, 1e9, "y");
            inf.readEoln();

            ensuref(isfinite(x) && isfinite(y), "coordinate %d is not finite", i + 1);
            ensuref(points.insert({x, y}).second,
                    "duplicate coordinate at point index %d: (%s, %s)",
                    i + 1,
                    vtos(x).c_str(),
                    vtos(y).c_str());
        }
    }

    ensuref(caseCount > 0, "input must contain at least one case");
    inf.readEof();
}
