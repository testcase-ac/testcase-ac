#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int minRemovedForOceanView(const vector<int>& heights) {
    vector<int> best(heights.size(), 1);
    int longest = 0;
    for (int i = 0; i < int(heights.size()); ++i) {
        for (int j = 0; j < i; ++j) {
            if (heights[j] < heights[i]) {
                best[i] = max(best[i], best[j] + 1);
            }
        }
        longest = max(longest, best[i]);
    }
    return int(heights.size()) - longest;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 50, "N");
        inf.readEoln();

        vector<int> heights = inf.readInts(n, 1, 1000, "height");
        inf.readEoln();

        ensuref(minRemovedForOceanView(heights) <= 4,
                "minimum destroyed houses must be at most 4");
    }

    inf.readEof();
}
