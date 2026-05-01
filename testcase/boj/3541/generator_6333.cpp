#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of elevators m
    double pm = rnd.next();
    int m;
    if (pm < 0.3) {
        m = rnd.next(1, 3);
    } else if (pm < 0.7) {
        m = rnd.next(4, 10);
    } else {
        m = rnd.next(11, 15);
    }

    // Hyper-parameter: number of button presses n
    double pn = rnd.next();
    int n;
    if (pn < 0.3) {
        n = rnd.next(1, 10);
    } else if (pn < 0.6) {
        n = rnd.next(11, 1000);
    } else {
        n = rnd.next(1001, 1000000);
    }

    vector<pair<int,int>> elev;
    for (int i = 0; i < m; i++) {
        double p = rnd.next();
        int u, d;
        if (p < 0.25) {
            // more down than up
            u = rnd.next(1, 500);
            d = rnd.next(u + 1, 1000);
        } else if (p < 0.5) {
            // more up than down
            d = rnd.next(1, 500);
            u = rnd.next(d + 1, 1000);
        } else if (p < 0.65) {
            // equal up and down
            u = rnd.next(1, 1000);
            d = u;
        } else if (p < 0.8) {
            // both moves even (gcd>1)
            int g = rnd.next(1, 500);
            u = 2 * g;
            d = 2 * g;
        } else {
            // wide random
            u = rnd.next(1, 1000);
            d = rnd.next(1, 1000);
        }
        elev.emplace_back(u, d);
    }

    // Output the test case
    println(n, m);
    for (auto &pr : elev) {
        println(pr.first, pr.second);
    }

    return 0;
}
