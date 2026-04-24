#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for total distance d
    int d;
    if (rnd.next() < 0.2) {
        // small total distance
        d = rnd.next(10, 100);
    } else {
        // large total distance
        d = rnd.next(1000, 1000000000);
    }

    // Number of small islands (keep small for hand-checking)
    int n = rnd.next(0, 10);
    // Number to remove
    int m = rnd.next(0, n);

    // Generate n distinct positions in (0, d), with varied clustering
    set<int> S;
    while ((int)S.size() < n) {
        double r = rnd.next();
        int x;
        if (r < 0.3) {
            // uniform anywhere
            x = rnd.next(1, d - 1);
        } else if (r < 0.65) {
            // cluster near start (weighted minimum)
            x = rnd.wnext(d, -2) + 1;
        } else {
            // cluster near end (weighted maximum)
            x = rnd.wnext(d, 2) + 1;
        }
        // clamp to valid range
        if (x < 1) x = 1;
        if (x > d - 1) x = d - 1;
        S.insert(x);
    }

    // Shuffle to avoid sorted input
    vector<int> pos(S.begin(), S.end());
    shuffle(pos.begin(), pos.end());

    // Output
    println(d, n, m);
    for (int x : pos) {
        println(x);
    }

    return 0;
}
