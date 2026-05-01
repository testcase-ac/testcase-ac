#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<array<int, 3>> tests;

    // Some fixed interesting cases
    tests.push_back({1, 1, 1});
    tests.push_back({1, 2, 3});  // sample
    tests.push_back({3, 2, 4});  // sample
    tests.push_back({60, 60, 60});
    tests.push_back({1, 60, 60});
    tests.push_back({60, 1, 60});
    tests.push_back({60, 60, 1});

    int base = (int)tests.size();
    int extra = rnd.next(0, 13); // total T between base and base+13 (7..20)
    int T = base + extra;

    for (int i = 0; i < extra; ++i) {
        int type = rnd.next(0, 5);
        array<int, 3> cur;

        if (type == 0) {
            // all equal
            int n = rnd.next(1, 60);
            cur = {n, n, n};
        } else if (type == 1) {
            // one dimension is 1
            int pos = rnd.next(0, 2);
            cur = {rnd.next(1, 60), rnd.next(1, 60), rnd.next(1, 60)};
            cur[pos] = 1;
        } else if (type == 2) {
            // two equal, one different
            int common = rnd.next(1, 60);
            int other = rnd.next(1, 60);
            int pos = rnd.next(0, 2);
            cur = {common, common, common};
            cur[pos] = other;
        } else if (type == 3) {
            // clustered around a base
            int baseVal = rnd.next(1, 60);
            for (int j = 0; j < 3; ++j) {
                int delta = rnd.next(-2, 2);
                int v = baseVal + delta;
                if (v < 1) v = 1;
                if (v > 60) v = 60;
                cur[j] = v;
            }
        } else if (type == 4) {
            // extremes mostly
            int choices[] = {1, 2, 3, 59, 60};
            for (int j = 0; j < 3; ++j) {
                cur[j] = choices[rnd.next(0, 4)];
            }
        } else {
            // sorted ascending or descending
            vector<int> v(3);
            for (int j = 0; j < 3; ++j) v[j] = rnd.next(1, 60);
            sort(v.begin(), v.end());
            if (rnd.next(0, 1) == 0)
                cur = {v[0], v[1], v[2]};
            else
                cur = {v[2], v[1], v[0]};
        }

        tests.push_back(cur);
    }

    println(T);
    for (auto &tr : tests) {
        println(tr[0], tr[1], tr[2]);
    }

    return 0;
}
