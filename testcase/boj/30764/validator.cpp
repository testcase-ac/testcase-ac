#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int a = inf.readInt(1, 1000000, "a");
    inf.readSpace();
    int b = inf.readInt(1, a, "b");
    inf.readSpace();
    int c = inf.readInt(1, b, "c");
    inf.readEoln();

    vector<pair<int, int>> trips;
    trips.reserve(n);
    for (int i = 0; i < n; ++i) {
        int l = inf.readInt(1, a, "l_i");
        inf.readSpace();
        int r = inf.readInt(l, a, "r_i");
        inf.readEoln();
        trips.push_back({l, r});
    }

    sort(trips.begin(), trips.end());
    for (int i = 1; i < n; ++i) {
        ensuref(trips[i - 1].second < trips[i].first,
                "trips overlap: [%d, %d] and [%d, %d]",
                trips[i - 1].first, trips[i - 1].second,
                trips[i].first, trips[i].second);
    }

    inf.readEof();
}
