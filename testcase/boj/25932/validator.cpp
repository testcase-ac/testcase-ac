#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: the statement only says n is positive; use the local default cap.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        set<int> seen;
        for (int i = 1; i <= 10; ++i) {
            int jersey = inf.readInt(11, 99, "jersey");
            ensuref(seen.insert(jersey).second,
                    "duplicate jersey number in case %d: %d", tc, jersey);

            if (i < 10) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
