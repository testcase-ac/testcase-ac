#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readSpace();
    int t = inf.readInt(0, n, "t");
    inf.readEoln();

    vector<bool> built(n + 1, false);
    for (int i = 1; i <= m; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int building = inf.readInt(1, n, "initial_building");
        ensuref(!built[building], "duplicate initially built building: %d", building);
        built[building] = true;
    }
    inf.readEoln();

    int maxKinds = min(n, 30);
    for (int building = 1; building <= n; ++building) {
        int count = inf.readInt(1, maxKinds, "produced_count");
        vector<bool> seen(n + 1, false);
        for (int j = 1; j <= count; ++j) {
            inf.readSpace();
            int resource = inf.readInt(1, n, "produced_resource");
            ensuref(!seen[resource],
                    "duplicate produced resource %d for building %d", resource, building);
            seen[resource] = true;
        }
        inf.readEoln();
    }

    vector<bool> hasRequirements(n + 1, false);
    for (int i = 1; i <= n - m; ++i) {
        int building = inf.readInt(1, n, "required_building");
        ensuref(!built[building], "already built building has requirements line: %d", building);
        ensuref(!hasRequirements[building],
                "duplicate requirements line for building: %d", building);
        hasRequirements[building] = true;

        inf.readSpace();
        int count = inf.readInt(1, maxKinds, "required_count");
        vector<bool> seen(n + 1, false);
        for (int j = 1; j <= count; ++j) {
            inf.readSpace();
            int resource = inf.readInt(1, n, "required_resource");
            ensuref(!seen[resource],
                    "duplicate required resource %d for building %d", resource, building);
            seen[resource] = true;
        }
        inf.readEoln();
    }

    for (int building = 1; building <= n; ++building) {
        ensuref(built[building] || hasRequirements[building],
                "missing requirements line for unbuilt building: %d", building);
    }

    inf.readEof();
}
