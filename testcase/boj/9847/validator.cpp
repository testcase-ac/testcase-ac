#include "testlib.h"

#include <map>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 500, "a");
    inf.readSpace();
    int b = inf.readInt(1, 500, "b");
    inf.readSpace();
    int c = inf.readInt(1, 500, "c");
    inf.readSpace();
    int d = inf.readInt(1, 500, "d");
    inf.readEoln();

    vector<vector<int>> sets(4);
    vector<int> sizes = {a, b, c, d};
    for (int i = 0; i < 4; ++i) {
        set<int> seen;
        for (int j = 0; j < sizes[i]; ++j) {
            int x = inf.readInt(-60000, 60000, format("set_%d_%d", i + 1, j + 1));
            inf.readEoln();
            // CHECK: The statement describes the inputs as sets, so duplicate
            // elements within one listed set are rejected.
            ensuref(seen.insert(x).second, "duplicate value %d in set %d", x, i + 1);
            sets[i].push_back(x);
        }
    }

    map<int, long long> abSums;
    for (int x : sets[0]) {
        for (int y : sets[1]) {
            ++abSums[x + y];
        }
    }

    long long zeroSumSelections = 0;
    for (int x : sets[2]) {
        for (int y : sets[3]) {
            auto it = abSums.find(-(x + y));
            if (it != abSums.end()) {
                zeroSumSelections += it->second;
                ensuref(zeroSumSelections <= 1, "more than one zero-sum selection exists");
            }
        }
    }
    ensuref(zeroSumSelections == 1, "exactly one zero-sum selection must exist");

    inf.readEof();
}
