#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 20, "Z");
    inf.readEoln();

    long long totalClasses = 0;
    for (int caseIndex = 1; caseIndex <= z; ++caseIndex) {
        setTestCase(caseIndex);

        int c = inf.readInt(1, 25, "C");
        inf.readSpace();
        int t = inf.readInt(1, 1000, "T");
        inf.readSpace();
        int l = inf.readInt(1, 1000000, "L");
        inf.readEoln();

        totalClasses += 1LL * c * t;
        // CHECK: The statement bounds each case but does not cap aggregate input size.
        ensuref(totalClasses <= 25000,
                "aggregate class count exceeds one largest test case: %lld",
                totalClasses);

        for (int category = 1; category <= c; ++category) {
            set<int> positions;
            for (int classIndex = 1; classIndex <= t; ++classIndex) {
                int p = inf.readInt(0, l, "P_ij");
                inf.readSpace();
                inf.readInt(1, 1000000, "E_ij");
                inf.readEoln();

                ensuref(positions.insert(p).second,
                        "duplicate location %d in category %d", p, category);
            }
        }
    }

    inf.readEof();
}
