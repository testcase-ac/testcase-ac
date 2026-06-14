#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalPreferenceIds = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 99, "N");
        inf.readEoln();

        // CHECK: T has no statement bound; keep total scalar input under the local practical cap.
        totalPreferenceIds += 2LL * n * n;
        ensuref(totalPreferenceIds < 5000000LL,
                "too many preference ids across all test cases");

        for (int side = 0; side < 2; ++side) {
            for (int i = 1; i <= n; ++i) {
                vector<int> seen(n + 1, 0);
                for (int j = 1; j <= n; ++j) {
                    if (j > 1) {
                        inf.readSpace();
                    }
                    int id = inf.readInt(1, n, "preference_id");
                    ensuref(!seen[id], "duplicate id %d in preference list %d", id, i);
                    seen[id] = 1;
                }
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
