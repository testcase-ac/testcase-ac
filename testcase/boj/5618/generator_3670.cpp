#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n = 2 or 3
    int n = rnd.any(vector<int>{2, 3});

    // Hyper: decide gcd G; sometimes 1, sometimes small, sometimes large
    int G;
    double p = rnd.next();
    if (p < 0.3) {
        G = 1;
    } else if (p < 0.6) {
        G = rnd.next(2, 50);
    } else {
        // larger G but keep within bounds
        G = rnd.wnext(100000000, -1);
        if (G < 51) G = rnd.next(51, 100000);
    }
    // Ensure G not too large so that Yi*G <= 1e8
    G = min(G, 100000000);

    vector<int> ys;
    int current_g = 0;
    for (int i = 0; i < n; i++) {
        // max multiplier to fit within 1e8
        int maxY = 100000000 / G;
        if (maxY < 1) maxY = 1;
        // pick a random y
        int y;
        // hyper: mix small and large y
        if (rnd.next() < 0.7) {
            int up = min(maxY, 20);
            y = rnd.next(1, up);
        } else {
            y = rnd.next(1, maxY);
        }
        // ensure gcd of all ys is 1
        if (i == 0) {
            current_g = y;
        } else {
            int g2 = gcd(current_g, y);
            if (g2 > 1) {
                y /= g2; // remove common factor
            }
            current_g = gcd(current_g, y);
        }
        if (y < 1) y = 1;
        ys.push_back(y);
    }
    // It's possible current_g > 1 only if all y=1; but gcd(1,1,..)=1 so OK

    // Build the actual numbers and shuffle
    vector<int> a;
    for (int y : ys) {
        long long val = 1LL * y * G;
        if (val < 1) val = 1;
        if (val > 100000000) val = 100000000;
        a.push_back((int)val);
    }
    shuffle(a.begin(), a.end());

    // Output
    println(n);
    println(a);

    return 0;
}
