#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias sometimes small, sometimes large
    int t = rnd.next(-2, 2);
    int N = rnd.wnext(14, t) + 1;  // 1 <= N <= 14

    // Prepare probabilities p[0]=E, p[1]=W, p[2]=S, p[3]=N
    vector<int> p(4, 0);
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // Uniform
        p = {25, 25, 25, 25};
    } else if (mode == 1) {
        // Bi-directional: either opposite or perpendicular
        int kind = rnd.next(0, 1);
        if (kind == 0) {
            // Opposite: choose either E-W or S-N
            if (rnd.next(0, 1) == 0) {
                int x = rnd.next(1, 99);
                p[0] = x; p[1] = 100 - x;
            } else {
                int x = rnd.next(1, 99);
                p[2] = x; p[3] = 100 - x;
            }
        } else {
            // Perpendicular: choose dir and a non-opposite
            int d1 = rnd.next(0, 3);
            int opp = (d1 < 2 ? d1 ^ 1 : d1 ^ 1);
            vector<int> cand;
            for (int d = 0; d < 4; d++)
                if (d != d1 && d != opp) cand.push_back(d);
            int d2 = rnd.any(cand);
            int x = rnd.next(1, 99);
            p[d1] = x;
            p[d2] = 100 - x;
        }
    } else if (mode == 2) {
        // Skewed: one heavy direction, rest share the remainder
        int heavy = rnd.next(0, 3);
        int heavyW = rnd.next(50, 100);
        int rem = 100 - heavyW;
        // generate 2 cut points
        vector<int> cuts = { rnd.next(0, rem), rnd.next(0, rem) };
        sort(cuts.begin(), cuts.end());
        vector<int> share = { cuts[0], cuts[1] - cuts[0], rem - cuts[1] };
        p[heavy] = heavyW;
        int idx = 0;
        for (int d = 0; d < 4; d++) {
            if (d == heavy) continue;
            p[d] = share[idx++];
        }
    } else {
        // Fully random distribution of 4 parts summing to 100
        vector<int> cuts = { rnd.next(0, 100), rnd.next(0, 100), rnd.next(0, 100) };
        sort(cuts.begin(), cuts.end());
        p[0] = cuts[0];
        p[1] = cuts[1] - cuts[0];
        p[2] = cuts[2] - cuts[1];
        p[3] = 100 - cuts[2];
    }

    // Output
    println(N, p[0], p[1], p[2], p[3]);
    return 0;
}
