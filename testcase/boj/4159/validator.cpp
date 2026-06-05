#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    while (true) {
        int n = inf.readInt(0, 1423, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++testCaseCount;
        setTestCase(testCaseCount);

        set<int> positions;
        bool hasDawsonCreek = false;
        for (int i = 0; i < n; ++i) {
            int position = inf.readInt(0, 1422, "position");
            inf.readEoln();

            ensuref(positions.insert(position).second,
                    "duplicate charging station position at row %d: %d", i + 1, position);
            hasDawsonCreek = hasDawsonCreek || position == 0;
        }

        ensuref(hasDawsonCreek, "charging station at Dawson Creek position 0 is missing");
    }

    // CHECK: The statement gives no scenario-count bound; keep the local default.
    ensuref(testCaseCount <= 100000, "too many scenarios: %d", testCaseCount);

    inf.readEof();
}
