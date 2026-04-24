#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for size
    int m = rnd.next(1, 10);  // number of cosmetics
    int n = rnd.next(1, 10);  // number of evaluators

    // Output header
    println(m, n);

    // We will vary r-ness by weighted next
    vector<int> tvals = {-2, -1, 0, 1, 2};

    for (int i = 0; i < n; i++) {
        // number of ranked cosmetics for this evaluator
        int r = rnd.wnext(m + 1, rnd.any(tvals));  // in [0, m]

        // prepare a random order of cosmetics
        vector<int> perm(m);
        iota(perm.begin(), perm.end(), 0);
        shuffle(perm.begin(), perm.end());

        // initialize all as unranked = 0
        vector<int> pref(m, 0);

        if (r > 0) {
            // choose how many tie-groups among the r ranked cosmetics
            int g = rnd.next(1, r);

            // pick cut points to form g segments in [0..r)
            vector<int> cuts;
            cuts.push_back(0);
            if (g > 1) {
                vector<int> pts(r - 1);
                iota(pts.begin(), pts.end(), 1);
                shuffle(pts.begin(), pts.end());
                for (int k = 0; k < g - 1; k++) {
                    cuts.push_back(pts[k]);
                }
            }
            cuts.push_back(r);
            sort(cuts.begin(), cuts.end());

            // assign group values (non-consecutive, positive)
            vector<int> gval(g);
            int cur = rnd.next(1, 3);
            for (int gi = 0; gi < g; gi++) {
                gval[gi] = cur;
                if (gi + 1 < g) {
                    cur += rnd.next(1, 5);
                }
            }

            // fill preferences
            for (int gi = 0; gi < g; gi++) {
                for (int idx = cuts[gi]; idx < cuts[gi + 1]; idx++) {
                    int cosmetic = perm[idx];
                    pref[cosmetic] = gval[gi];
                }
            }
        }

        // print this evaluator's list
        println(pref);
    }

    return 0;
}
