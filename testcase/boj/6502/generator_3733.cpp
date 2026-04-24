#include "testlib.h"
#include <cmath>
#include <vector>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 10);
    vector<array<int,3>> cases;
    cases.reserve(T);

    for (int i = 0; i < T; i++) {
        int r = rnd.next(1, 1000);

        // Determine which case types are valid for this r
        vector<int> types;
        // Type 1: both dims <=2r, but diagonal > 2r -> only possible if r < 707
        if (r < 707) types.push_back(1);
        // Type 2: both dims <=2r, diagonal <=2r -> always possible
        types.push_back(2);
        // Type 3: one dimension >2r -> only if 2r+1 <= 1000
        if (2*r + 1 <= 1000) types.push_back(3);
        // Type 4: totally random
        types.push_back(4);

        int typ = rnd.any(types);
        int w, l;

        if (typ == 1) {
            // Construct dims <=2r but diagonal too large
            if (2*r <= 1000) {
                // use w=2r-1, l=2r
                w = 2*r - 1;
                l = 2*r;
            } else {
                // r between 501 and 706 inclusive: max dims=1000 give half-diag>r
                w = 1000;
                l = 1000;
            }
        }
        else if (typ == 2) {
            // Construct dims that fit: w=l=floor(r*sqrt(2))
            int md = floor(r * sqrt(2.0));
            if (md < 1) md = 1;
            if (md > 1000) md = 1000;
            w = md;
            l = md;
        }
        else if (typ == 3) {
            // One dimension >2r
            w = 2*r + 1;
            l = rnd.next(w, 1000);
        }
        else {
            // Completely random valid case
            w = rnd.next(1, 1000);
            l = rnd.next(w, 1000);
        }

        cases.push_back({r, w, l});
    }

    // Output all test cases
    for (auto &c : cases) {
        println(c[0], c[1], c[2]);
    }
    // Termination line
    println(0);

    return 0;
}
