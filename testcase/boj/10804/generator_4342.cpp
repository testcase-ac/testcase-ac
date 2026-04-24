#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int,int>> segs;
    // Hyper-parameters for diversity
    int cnt_point = rnd.next(0, 2);    // segments of length 1
    int cnt_medium = rnd.next(0, 3);   // segments of moderate length
    int cnt_full = rnd.next(0, 2);     // full reversals [1,20]
    int cnt_rest = 10 - cnt_point - cnt_medium - cnt_full;

    // Point segments (length = 1)
    for (int i = 0; i < cnt_point; i++) {
        int a = rnd.next(1, 20);
        segs.emplace_back(a, a);
    }
    // Full segments (length = 20)
    for (int i = 0; i < cnt_full; i++) {
        segs.emplace_back(1, 20);
    }
    // Medium segments (length 2 to 10)
    for (int i = 0; i < cnt_medium; i++) {
        int len = rnd.next(2, 10);
        int a = rnd.next(1, 21 - len);
        segs.emplace_back(a, a + len - 1);
    }
    // Rest segments with weighted length distribution
    vector<int> tvals = { -4, -2, 0, 2, 4 };
    for (int i = 0; i < cnt_rest; i++) {
        int t = rnd.any(tvals);
        int len = rnd.wnext(20, t) + 1;
        if (len > 20) len = 20;
        int a = rnd.next(1, 21 - len);
        segs.emplace_back(a, a + len - 1);
    }

    // Shuffle to mix segment types
    shuffle(segs.begin(), segs.end());

    // Output exactly 10 intervals
    for (auto &p : segs) {
        println(p.first, p.second);
    }

    return 0;
}
