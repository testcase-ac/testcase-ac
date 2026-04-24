#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of clothes and runs
    int n = rnd.next(1, 10);
    int k = rnd.next(1, 3);

    // choose a temperature range [t_low, t_high]
    int t_low = rnd.next(40, 90);
    int t_high = rnd.next(t_low, 100);
    int trange = t_high - t_low + 1;

    vector<pair<int,int>> clothes;
    clothes.reserve(n);
    for(int i = 0; i < n; i++) {
        // generate t_i with bias: half low, half high, half uniform
        int t;
        double p = rnd.next();
        if (p < 0.3) {
            // bias towards low end
            t = rnd.wnext(trange, -1) + t_low;
        } else if (p < 0.6) {
            // bias towards high end
            t = rnd.wnext(trange, 1) + t_low;
        } else {
            // uniform
            t = rnd.next(t_low, t_high);
        }

        // generate w_i: zeros, small, or large
        int w;
        double q = rnd.next();
        if (q < 0.2) {
            w = 0;
        } else if (q < 0.6) {
            w = rnd.wnext(101, -1);  // bias small
        } else {
            w = rnd.wnext(101, 1);   // bias large
        }
        clothes.emplace_back(t, w);
    }

    // shuffle the clothes order for diversity
    shuffle(clothes.begin(), clothes.end());

    // output
    println(n, k);
    for (auto &cw : clothes) {
        println(cw.first, cw.second);
    }
    return 0;
}
