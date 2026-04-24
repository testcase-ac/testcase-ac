#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of phones
    int n = rnd.next(2, 10);
    // Maximum coordinate value
    int maxC = rnd.next(1, 20);

    // Hyper-parameters for diversity
    bool hasExtreme = rnd.next(0, 4) == 0;   // include a phone with all coords = maxC
    bool hasLow     = rnd.next(0, 4) == 0;   // include a phone with all coords = 1
    bool correlated = rnd.next(0, 1) == 0;   // generate correlated coords

    vector<array<int,3>> v;

    if (hasExtreme) v.push_back({maxC, maxC, maxC});
    if (hasLow)     v.push_back({1, 1, 1});

    // Clamp helper
    auto clamp = [&](int val) {
        if (val < 1) return 1;
        if (val > maxC) return maxC;
        return val;
    };

    int rem = n - (int)v.size();
    for (int i = 0; i < rem; i++) {
        int x, y, z;
        if (correlated) {
            int base = rnd.next(1, maxC);
            x = base;
            y = clamp(base + rnd.next(-2, 2));
            z = clamp(base + rnd.next(-2, 2));
        } else {
            x = rnd.next(1, maxC);
            y = rnd.next(1, maxC);
            z = rnd.next(1, maxC);
        }
        // Occasional two-high-one-low corner case
        if (rnd.next(0, 9) == 0) {
            int d = rnd.next(1, 3);
            if (d == 1) { x = maxC; y = maxC; z = rnd.next(1, maxC); }
            else if (d == 2) { x = maxC; z = maxC; y = rnd.next(1, maxC); }
            else            { y = maxC; z = maxC; x = rnd.next(1, maxC); }
        }
        v.push_back({x, y, z});
    }

    // Randomize order so the best index isn't obvious
    shuffle(v.begin(), v.end());

    // Output
    println((int)v.size());
    for (auto &t : v) {
        println(t[0], t[1], t[2]);
    }

    return 0;
}
