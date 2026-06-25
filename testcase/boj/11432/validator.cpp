#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    long long totalPlaneIds = 0;
    for (int dataSet = 1; dataSet <= k; ++dataSet) {
        setTestCase(dataSet);

        int m = inf.readInt(0, 200, "m");
        inf.readSpace();
        int n = inf.readInt(0, 200, "n");
        inf.readEoln();

        for (int pilot = 1; pilot <= n; ++pilot) {
            int mi = inf.readInt(0, m, "m_i");
            set<int> planes;
            for (int j = 1; j <= mi; ++j) {
                inf.readSpace();
                int plane = inf.readInt(1, m, "plane");
                ensuref(planes.insert(plane).second,
                        "duplicate plane %d for pilot %d", plane, pilot);
            }
            inf.readEoln();

            totalPlaneIds += mi;
            // CHECK: K has no statement upper bound; cap total capability ids
            // to keep validator inputs below the local scalar-token limit.
            ensuref(totalPlaneIds <= 5000000,
                    "too many listed pilot-plane capabilities: %lld", totalPlaneIds);
        }
    }

    inf.readEof();
}
