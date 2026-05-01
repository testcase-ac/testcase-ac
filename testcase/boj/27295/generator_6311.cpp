#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of points and fixed intercept
    int n = rnd.next(1, 10);
    int b = rnd.next(-5, 5);

    // mode: 0 = EZPZ case, 1 = integer slope, 2 = fractional slope
    int mode = rnd.next(0, 2);

    vector<int> x(n), y(n);

    if (mode == 0) {
        // sum_x = 0 and sum(b - y) = 0 => any a1 works => EZPZ
        for (int i = 0; i < n; i++) {
            x[i] = 0;
            y[i] = b;
        }
    } else {
        // generate x such that sum_x != 0, and for mode 2 also |sum_x| > 1
        int Sx;
        do {
            for (int i = 0; i < n; i++) {
                x[i] = rnd.next(-5, 5);
            }
            Sx = accumulate(x.begin(), x.end(), 0);
        } while (Sx == 0 || (mode == 2 && abs(Sx) <= 1));

        if (mode == 1) {
            // integer slope: choose k so that sum(yi - b) = k * Sx
            int k = rnd.next(-3, 3);
            for (int i = 0; i < n; i++) {
                y[i] = b + k * x[i];
            }
        } else {
            // fractional slope: choose k and r so that sum(yi - b) = k*Sx + r,
            // with gcd(r, |Sx|) = 1 and 1 <= r < |Sx|
            int absSx = abs(Sx);
            int r;
            do {
                r = rnd.next(1, absSx - 1);
            } while (std::gcd(r, absSx) != 1);
            int k = rnd.next(-3, 3);
            // assign the extra remainder r to the first point
            y[0] = b + k * x[0] + r;
            for (int i = 1; i < n; i++) {
                y[i] = b + k * x[i];
            }
        }
    }

    // assemble and shuffle points
    vector<pair<int,int>> pts;
    for (int i = 0; i < n; i++) {
        pts.emplace_back(x[i], y[i]);
    }
    shuffle(pts.begin(), pts.end());

    // output
    println(n, b);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
