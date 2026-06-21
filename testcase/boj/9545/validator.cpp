#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(0, 676, "n");
        inf.readEoln();

        set<string> pairs;
        for (int i = 1; i <= n; ++i) {
            string pair = inf.readToken("[a-z]{2}", "pair");
            inf.readEoln();

            ensuref(pairs.insert(pair).second,
                    "duplicate explosive pair in test case %d at index %d: %s",
                    tc, i, pair.c_str());
        }
    }

    inf.readEof();
}
