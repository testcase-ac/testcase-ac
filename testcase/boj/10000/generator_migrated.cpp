#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int outer_r = rnd.next(8, 64);
    int branch_max = rnd.next(2, 4);
    int rad_lim = rnd.next(1, 4);
    double chance = rnd.next(0.5, 1.0);

    vector<pair<i64, i64>> circles;
    auto fill_inner = [&](auto self, i64 center, i64 rad, bool force=false) -> void {
        i64 left = center - rad, right = center + rad;
        
        if (!force) {
            // randomized branch
            if (rad <= rad_lim) { return; }
            double d = rnd.next(1.0);
            if (d > chance) { return; }
        }
        
        auto cuts = rnd.distinct(rnd.next(1ll, min(i64(branch_max), rad-1)), 1ll, rad-1);
        for (i64& x : cuts) { x *= 2; x += left; }
        cuts.push_back(left);
        cuts.push_back(right);
        sort(cuts.begin(), cuts.end());

        bool need_one = force;
        bool split = rnd.next(2);
        for (int i = 0; i < cuts.size()-1; i++) {
            i64 nleft = cuts[i], nright = cuts[i+1];
            i64 ncenter = (nleft + nright)/2, nrad = abs(nleft - nright)/2;
            if (need_one || split || rnd.next(2)) {
                need_one = false;
                circles.emplace_back(ncenter, nrad);
                self(self, ncenter, nrad);
            }
        }
    };

    fill_inner(fill_inner, 0, outer_r, true);
    shuffle(circles.begin(), circles.end());

    println(circles.size());
    for (auto &c : circles) {
        println(c.first, c.second);
    }
    return 0;
}
