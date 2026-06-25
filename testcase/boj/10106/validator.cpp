#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        vector<bool> seen(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            int car = inf.readInt(1, n, "car");
            inf.readEoln();

            ensuref(!seen[car],
                    "duplicate car number %d at position %d in case %d",
                    car,
                    i,
                    tc);
            seen[car] = true;
        }

        for (int car = 1; car <= n; ++car) {
            ensuref(seen[car], "missing car number %d in case %d", car, tc);
        }
    }

    inf.readEof();
    return 0;
}
