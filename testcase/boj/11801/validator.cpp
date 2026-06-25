#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int s = inf.readInt(1, 5000, "S");
        inf.readSpace();
        int n = inf.readInt(1, 50, "N");
        inf.readEoln();

        set<int> values;
        for (int i = 1; i <= n; ++i) {
            int v = inf.readInt(1, 5000, "V_i");
            inf.readSpace();
            inf.readInt(1, 5000, "C_i");
            inf.readEoln();

            ensuref(values.insert(v).second,
                    "coin value is repeated in test case %d at row %d: %d",
                    tc, i, v);
        }

        (void)s;
    }

    inf.readEof();
}
