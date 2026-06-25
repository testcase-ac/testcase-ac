#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int s = inf.readInt(1, 1000000, "S");
    inf.readEoln();

    ensuref(1LL * m * s <= 1000000LL, "M * S must be at most 10^6");

    set<vector<int>> preferenceLists;
    for (int i = 0; i < m; ++i) {
        vector<int> preference(s);
        vector<bool> seen(s + 1, false);

        for (int j = 0; j < s; ++j) {
            preference[j] = inf.readInt(1, s, "preference");
            ensuref(!seen[preference[j]],
                    "duplicate song %d in member %d preference list",
                    preference[j],
                    i + 1);
            seen[preference[j]] = true;

            if (j + 1 < s) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }

        ensuref(preferenceLists.insert(preference).second,
                "duplicate preference list for member %d",
                i + 1);
    }

    inf.readEof();
}
