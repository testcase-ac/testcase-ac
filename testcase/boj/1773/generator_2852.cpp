#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small sizes for hand checking
    int N = rnd.next(1, 10);
    int C = rnd.next(1, 100);

    vector<int> periods;

    // Hyper-parameters: sometimes force period = 1
    if (rnd.next() < 0.3) {
        periods.push_back(1);
    }
    // Sometimes force period = C, but not exceeding N entries
    if (rnd.next() < 0.3 && (int)periods.size() < N) {
        periods.push_back(C);
    }

    // Fill remaining periods with diverse strategies
    while ((int)periods.size() < N) {
        double r = rnd.next();
        if (r < 0.3) {
            // small period in [1, C/10]
            int mx = max(1, C / 10);
            periods.push_back(rnd.next(1, mx));
        } else if (r < 0.6) {
            // large period near C
            int lo = max(1, C - 10);
            periods.push_back(rnd.next(lo, C));
        } else {
            // weighted sampling for extra diversity
            int t = rnd.any(vector<int>{-3, -1, 1, 3});
            // rnd.wnext(C, t) returns [0, C-1], so +1 gives [1, C]
            periods.push_back(rnd.wnext(C, t) + 1);
        }
    }

    // Shuffle to randomize order
    shuffle(periods.begin(), periods.end());

    // Output in the required format
    println(N, C);
    for (int p : periods) {
        println(p);
    }

    return 0;
}
