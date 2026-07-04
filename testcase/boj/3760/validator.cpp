#include "testlib.h"

using namespace std;

int readFreeInt(int minValue, int maxValue, const string& name) {
    inf.skipBlanks();
    return inf.readInt(minValue, maxValue, name);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no numeric bounds; these caps keep inputs
    // finite while allowing representative O(n^2) datasets.
    const int maxN = 3000;
    const int maxCost = 1000000000;
    const long long maxMaintenanceValues = 5000000LL;

    long long totalMaintenanceValues = 0;
    int dataset = 0;

    while (!inf.seekEof()) {
        ++dataset;
        setTestCase(dataset);

        // CHECK: Costs are not bounded in the statement. Treat costs as
        // nonnegative int-sized values because the problem describes costs.
        int c = readFreeInt(0, maxCost, "c");

        // CHECK: The number of years has no stated upper bound. A dataset with
        // no years would not match the described period over which a computer is owned.
        int n = readFreeInt(1, maxN, "n");

        long long valuesInDataset = 1LL * n * (n + 1) / 2;
        ensuref(totalMaintenanceValues + valuesInDataset <= maxMaintenanceValues,
                "too many maintenance values across datasets: %lld",
                totalMaintenanceValues + valuesInDataset);
        totalMaintenanceValues += valuesInDataset;

        for (int y = 1; y <= n; ++y) {
            for (int z = y; z <= n; ++z) {
                string name = "m_" + to_string(y) + "_" + to_string(z);
                readFreeInt(0, maxCost, name);
            }
        }
    }

    ensuref(dataset > 0, "at least one dataset is required");
    inf.readEof();
}
