#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of people
    int N = rnd.next(2, 8);

    // Randomize weight and height ranges
    int weight_low  = rnd.next(40, 60);
    int weight_high = rnd.next(max(weight_low + 10, 61), 120);
    int height_low  = rnd.next(150, 170);
    int height_high = rnd.next(max(height_low + 10, 171), 200);

    // Choose distribution type:
    // 0 = independent uniform
    // 1 = positively correlated (taller tends to weigh more)
    // 2 = negatively correlated (taller tends to weigh less)
    int dist_type = rnd.next(0, 2);

    vector<pair<int,int>> people;
    for (int i = 0; i < N; i++) {
        int w, h;
        if (dist_type == 0) {
            // Independent uniform
            w = rnd.next(weight_low, weight_high);
            h = rnd.next(height_low, height_high);

        } else if (dist_type == 1) {
            // Positive correlation: h ≈ w + noise
            w = rnd.next(weight_low, weight_high);
            int noise = rnd.next(-5, 5);
            h = w + noise;
            h = min(max(h, height_low), height_high);

        } else {
            // Negative correlation: h ≈ reversed linear function of w + noise
            w = rnd.next(weight_low, weight_high);
            double slope = double(height_low - height_high) / (weight_high - weight_low);
            double base  = height_high + (w - weight_low) * slope;
            int noise    = rnd.next(-5, 5);
            h = int(round(base)) + noise;
            h = min(max(h, height_low), height_high);
        }

        people.emplace_back(w, h);
    }

    // Output
    println(N);
    for (auto &p : people) {
        println(p.first, p.second);
    }

    return 0;
}
