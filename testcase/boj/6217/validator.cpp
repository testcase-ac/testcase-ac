#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int tallestIndex = inf.readInt(1, n, "I");
    inf.readSpace();
    int tallestHeight = inf.readInt(1, 1000000, "H");
    inf.readSpace();
    int r = inf.readInt(0, 10000, "R");
    inf.readEoln();

    set<pair<int, int>> intervals;
    for (int i = 1; i <= r; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readEoln();

        ensuref(a != b, "visibility line %d has equal endpoints: %d", i, a);

        // CHECK: The statement does not forbid repeated visibility lines.
        // Repeated lines carry the same information, so they are accepted.
        if (a > b) {
            swap(a, b);
        }
        intervals.insert({a, b});
    }

    // The statement guarantees that all constraints are satisfiable with
    // positive heights. For this input model, each unique interval lowers every
    // cow strictly between its endpoints by one from the tallest possible value.
    vector<int> delta(n + 2, 0);
    for (auto [left, right] : intervals) {
        ++delta[left + 1];
        --delta[right];
    }

    int coveringIntervals = 0;
    for (int cow = 1; cow <= n; ++cow) {
        coveringIntervals += delta[cow];
        int maximumPossibleHeight = tallestHeight - coveringIntervals;
        ensuref(maximumPossibleHeight >= 1,
                "cow %d cannot have a positive height: maximum is %d",
                cow,
                maximumPossibleHeight);
    }

    (void)tallestIndex;
    inf.readEof();
}
