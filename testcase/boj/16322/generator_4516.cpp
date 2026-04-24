#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Lawn size and number of mowers
    int l = rnd.next(1, 1000000);
    int m = rnd.next(1, 10);

    // Decide whether there is at least one feasible mower
    bool wantFeasible = rnd.next(0, 1);
    if (!wantFeasible && l <= 1) {
        // If lawn size is 1, any mower can do it => force feasible
        wantFeasible = true;
    }

    println(l, m);

    const string ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const string MID = ALPHA + " -";

    for (int i = 0; i < m; i++) {
        // Generate a random name (no commas, no leading/trailing spaces)
        int len = rnd.next(3, 10);
        string name;
        name.push_back(rnd.any(ALPHA));
        for (int j = 1; j < len - 1; j++) {
            name.push_back(rnd.any(MID));
        }
        name.push_back(rnd.any(ALPHA));

        // Price: 1..100000 with some weighting
        int wt = rnd.next(-2, 2);
        int price = 1 + rnd.wnext(100000, wt);

        int c, t, r;
        if (wantFeasible && i == 0) {
            // Ensure at least one feasible mower: c * t >= l
            t = rnd.next(1, 10080);
            // minimal rate to finish in one run
            int base = (l + t - 1) / t;
            if (base < 1) base = 1;
            if (base > 100) base = 100;
            c = base + rnd.next(0, max(0, 100 - base));
            if (c > 100) c = 100;
            // verify
            if ((long long)c * t < l) {
                // adjust rate
                c = (l + t - 1) / t;
                if (c > 100) c = 100;
            }
            r = rnd.next(1, 10080);
        } else {
            // Random mower
            t = rnd.next(1, 10080);
            c = rnd.next(1, 100);
            r = rnd.next(1, 10080);
            // If we want no feasible, enforce c * t < l
            if (!wantFeasible) {
                // ensure infeasible
                while ((long long)c * t >= l) {
                    t = rnd.next(1, 10080);
                    c = rnd.next(1, 100);
                }
            }
        }

        // Output one line: name,p,c,t,r
        printf("%s,%d,%d,%d,%d\n", name.c_str(), price, c, t, r);
    }

    return 0;
}
