#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int maxCoord = rnd.next(1, 20);
    double pLarge = rnd.next(0.0, 1.0);
    double pSmall = 0.0;
    if (pLarge < 1.0)
        pSmall = rnd.next(0.0, 1.0 - pLarge);

    int half = max(1, maxCoord / 2);
    int quarter = maxCoord / 4;

    vector<pair<int,int>> segs;
    segs.reserve(N);
    for (int i = 0; i < N; i++) {
        double u = rnd.next();
        int l, r;
        if (u < pLarge) {
            // large segment: spans at least half the range
            l = rnd.next(1, half);
            r = rnd.next(half, maxCoord);
        } else if (u < pLarge + pSmall) {
            // small segment: short length
            int len = rnd.next(0, quarter);
            l = rnd.next(1, maxCoord - len);
            r = l + len;
        } else {
            // mid-sized random segment
            l = rnd.next(1, maxCoord);
            r = rnd.next(1, maxCoord);
            if (l > r) swap(l, r);
        }
        segs.emplace_back(l, r);
    }

    // Shuffle to remove any order bias
    shuffle(segs.begin(), segs.end());

    // Output
    println(N);
    for (auto &pr : segs) {
        println(pr.first, pr.second);
    }

    return 0;
}
