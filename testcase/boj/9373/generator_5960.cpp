#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        // corridor width choices
        vector<int> widths = {5, 10, 15, 20, 50, 100};
        int w = rnd.any(widths);
        println(w);

        double p = rnd.next();
        if (p < 0.15) {
            // No sensors
            println(0);
        } else if (p < 0.30) {
            // Simple barrier: two sensors touching both walls
            println(2);
            int cy = rnd.next(-10, 10);
            int r1 = w + rnd.next(0, 10);
            int r2 = w + rnd.next(0, 10);
            println(0, cy, r1);
            println(w, cy + rnd.next(-5, 5), r2);
        } else {
            // Random sensors
            int maxn = 12;
            // At least 1 sensor, biased towards small n
            int n = rnd.wnext(maxn, -2) + 1; 
            println(n);
            for (int i = 0; i < n; ++i) {
                // choose wall or interior
                int t = rnd.next(0, 2);
                int x = (t == 0 ? 0 : (t == 1 ? w : rnd.next(0, w)));
                // y in [-100,100)
                int y = rnd.wnext(200, rnd.next(-1, 1)) - 100;
                int r;
                // occasionally large radius
                if (rnd.next() < 0.1) {
                    // radius up to twice the width
                    r = rnd.next(w + 1, w * 2);
                } else {
                    // radius up to width
                    r = rnd.wnext(w, rnd.next(-2, 2)) + 1;
                }
                println(x, y, r);
            }
        }
    }
    return 0;
}
