#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Scenario types:
    // 0: three distinct random values, shuffled
    // 1: two equal, one different, shuffled
    // 2: all equal, shuffled
    // 3: sorted increasing  (1, b, 99)
    // 4: sorted decreasing  (99, b, 1)
    int scenario = rnd.next(0, 4);
    vector<int> w;
    if (scenario == 0) {
        // three distinct
        while ((int)w.size() < 3) {
            int x = rnd.next(1, 99);
            bool ok = true;
            for (int v : w) if (v == x) { ok = false; break; }
            if (ok) w.push_back(x);
        }
        shuffle(w.begin(), w.end());
    } else if (scenario == 1) {
        // two equal, one different
        int x = rnd.next(1, 99);
        int y;
        do { y = rnd.next(1, 99); } while (y == x);
        w = {x, x, y};
        shuffle(w.begin(), w.end());
    } else if (scenario == 2) {
        // all equal
        int x = rnd.next(1, 99);
        w = {x, x, x};
        shuffle(w.begin(), w.end());
    } else if (scenario == 3) {
        // sorted increasing with extremes
        int b = rnd.next(2, 98);
        w = {1, b, 99};
    } else {
        // sorted decreasing with extremes
        int b = rnd.next(2, 98);
        w = {99, b, 1};
    }

    // Output three weights, one per line
    for (int v : w) {
        println(v);
    }
    return 0;
}
