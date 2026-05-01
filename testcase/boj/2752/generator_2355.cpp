/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> v;
    // 20% chance to test large values near the upper bound
    if (rnd.next(0, 4) == 0) {
        set<int> s;
        while ((int)s.size() < 3) {
            int x = rnd.next(999900, 1000000);
            s.insert(x);
        }
        for (int x : s) v.push_back(x);
        // shuffle to produce random order
        shuffle(v.begin(), v.end());
    } else {
        // small values for hand-checkable cases
        int hi = rnd.next(3, 20);
        v.resize(hi);
        iota(v.begin(), v.end(), 1);
        shuffle(v.begin(), v.end());
        v.resize(3);
    }

    // Output three distinct integers
    println(v[0], v[1], v[2]);
    return 0;
}
