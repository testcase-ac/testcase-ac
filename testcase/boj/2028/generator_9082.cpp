#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> autom = {1, 5, 6, 25, 76, 376, 625};
    set<int> autosSet(autom.begin(), autom.end());

    vector<int> v;
    int mode = rnd.next(0, 3); // 4 modes: 0,1,2,3

    if (mode == 0) {
        // Sample-like, small and easy to verify
        v = {1, 6, 76, 89};

        // Randomly remove one element to vary size/contents
        if ((int)v.size() > 1 && rnd.next(0, 1) == 0) {
            int pos = rnd.next(0, (int)v.size() - 1);
            v.erase(v.begin() + pos);
        }

        // Add some extra random testcases
        int maxExtra = 20 - (int)v.size();
        int extra = (maxExtra > 0) ? rnd.next(0, maxExtra) : 0;
        for (int i = 0; i < extra; ++i) {
            int opt = rnd.next(0, 2);
            if (opt == 0) {
                v.push_back(rnd.any(autom)); // definitely YES
            } else {
                v.push_back(rnd.next(1, 1000)); // arbitrary (may be YES or NO)
            }
        }
    } else if (mode == 1) {
        // Balanced random: mix YES and NO, ensure both exist
        int Tcand = rnd.next(5, 20);
        for (int i = 0; i < Tcand; ++i) {
            bool wantAuto = (rnd.next(0, 99) < 40); // 40% chance to pick automorphic
            if (wantAuto) {
                v.push_back(rnd.any(autom));
            } else {
                int x;
                do {
                    x = rnd.next(1, 1000);
                } while (autosSet.count(x)); // ensure non-automorphic
                v.push_back(x);
            }
        }
        bool hasAuto = false, hasNon = false;
        for (int x : v) {
            if (autosSet.count(x)) hasAuto = true;
            else hasNon = true;
        }
        if (!hasAuto) {
            v[0] = rnd.any(autom);
        }
        if (!hasNon) {
            for (int x = 1; x <= 1000; ++x) {
                if (!autosSet.count(x)) {
                    v.back() = x;
                    break;
                }
            }
        }
        shuffle(v.begin(), v.end());
    } else if (mode == 2) {
        // Boundary-focused tests
        vector<int> cand = {
            1, 2, 4, 5, 6, 7, 9,
            10, 11, 24, 25, 26,
            75, 76, 77,
            99, 100, 101,
            374, 375, 376, 377,
            624, 625, 626,
            998, 999, 1000
        };
        shuffle(cand.begin(), cand.end());
        int maxT = min(20, (int)cand.size());
        int Tcand = rnd.next(5, maxT);
        v.assign(cand.begin(), cand.begin() + Tcand);
    } else { // mode == 3
        // Automorphic-focused: many YES cases, maybe only YES
        int pattern = rnd.next(0, 2);
        if (pattern == 0) {
            // Each automorphic once, maybe truncated
            v = autom;
            shuffle(v.begin(), v.end());
            int Tcand = rnd.next(1, (int)v.size());
            v.resize(Tcand);
        } else if (pattern == 1) {
            // All YES, with repetitions
            int Tcand = rnd.next(1, 20);
            for (int i = 0; i < Tcand; ++i)
                v.push_back(rnd.any(autom));
            shuffle(v.begin(), v.end());
        } else {
            // Mix of automorphics and near values
            vector<int> base = {1, 5, 6, 25, 26, 24, 75, 76, 77, 375, 376, 377, 624, 625, 626};
            shuffle(base.begin(), base.end());
            int maxT = min(20, (int)base.size());
            int Tcand = rnd.next(3, maxT);
            v.assign(base.begin(), base.begin() + Tcand);
        }
    }

    if (v.empty()) {
        v.push_back(1); // fallback, should never happen
    }

    int T = (int)v.size();
    println(T);
    for (int x : v) {
        println(x);
    }

    return 0;
}
