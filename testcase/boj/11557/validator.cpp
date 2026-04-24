#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T (no explicit bound given, assume up to 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        set<int> seenL;
        setTestCase(tc);

        // Number of schools N
        int N = inf.readInt(1, 100, "N");
        inf.readEoln();

        for (int i = 0; i < N; i++) {
            // School name: 1 to 20 letters, no spaces
            string name = inf.readToken("[A-Za-z]{1,20}", "school_name");
            inf.readSpace();
            // Alcohol consumption L
            int L = inf.readInt(0, 10000000, "L");
            inf.readEoln();

            // Ensure no two schools have the same L in the same test case
            ensuref(seenL.count(L) == 0,
                    "Duplicate consumption value %d in test case %d at line %d",
                    L, tc, i+1);
            seenL.insert(L);
        }
    }

    inf.readEof();
    return 0;
}
