#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of suspects
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // Read all (arrival, duration) pairs
    vector<pair<int,int>> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        int a = inf.readInt(1, 1000000000, "a_i");
        inf.readSpace();
        int t = inf.readInt(1, 1000000000, "t_i");
        inf.readEoln();
        v.emplace_back(a, t);
    }

    // Check the global constraint:
    // No two suspects who arrived at the same time stayed for the same duration.
    sort(v.begin(), v.end());
    for (int i = 1; i < n; i++) {
        if (v[i].first == v[i-1].first) {
            ensuref(v[i].second != v[i-1].second,
                    "Two suspects arrived at time %d with the same duration %d",
                    v[i].first, v[i].second);
        }
    }

    inf.readEof();
    return 0;
}
