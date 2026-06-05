#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    set<vector<long long>> points;
    for (int i = 0; i < m; ++i) {
        vector<long long> point;
        point.reserve(n);
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            point.push_back(inf.readLong(-1000000000000LL, 1000000000000LL, "p_ij"));
        }
        inf.readEoln();

        ensuref(points.insert(point).second, "duplicate point at index %d", i + 1);
    }

    inf.readEof();
}
