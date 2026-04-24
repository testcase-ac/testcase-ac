#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of types
    int k = rnd.next(1, 5);
    // Hyper-parameter: total facilities, at least k, at most 10
    int n = rnd.next(k, 10);

    // Probability to use very wide location range
    double wideProb = rnd.next(0.0, 1.0);

    vector<pair<int,int>> facs;
    // Ensure at least one facility per type
    for (int t = 1; t <= k; ++t) {
        int loc;
        if (rnd.next() < 0.5) {
            // cluster near origin
            loc = rnd.next(-3, 3);
        } else {
            // some spread
            loc = rnd.next(-10, 10);
        }
        facs.emplace_back(loc, t);
    }
    // Add remaining facilities
    for (int i = 0; i < n - k; ++i) {
        int t = rnd.next(1, k);
        int loc;
        if (rnd.next() < wideProb) {
            // occasional very wide placement
            loc = rnd.next(-1000000000, 1000000000);
        } else if (rnd.next() < 0.5) {
            loc = rnd.next(-5, 5);
        } else {
            loc = rnd.next(-20, 20);
        }
        facs.emplace_back(loc, t);
    }

    // Shuffle so types and locations are in random order
    shuffle(facs.begin(), facs.end());

    // Output
    println(k, n);
    for (auto &p : facs) {
        println(p.first, p.second);
    }
    return 0;
}
