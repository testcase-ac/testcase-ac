#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: 1 or 2, with equal probability
    int K = rnd.next(0, 1) + 1;
    println(K);

    for (int tc = 1; tc <= K; ++tc) {
        // Choose sizes (kept small for readability)
        int n = rnd.next(1, 12);                  // number of friends
        int c = rnd.next(1, min(n, 12));          // number of cars (c <= n)
        int l = rnd.next(1, c);                   // number of regions (l <= c)

        println(n, c, l);

        // Hyper-parameters for this test case
        int friendDistType = rnd.next(0, 2);      // 0: each region at least one friend, 1: skewed, 2: random
        int drunkPattern   = rnd.next(0, 5);      // 0..5 different S/I patterns
        int carDistType    = rnd.next(0, 2);      // 0: balanced, 1: skewed, 2: random
        int capPattern     = rnd.next(0, 2);      // 0: small caps, 1: large caps, 2: mixed

        // ----- Generate friends -----
        vector<int> friendRegion(n);
        // Region distribution for friends
        if (friendDistType == 0) {
            // Ensure at least one friend per region (since l <= n)
            for (int i = 0; i < l; ++i)
                friendRegion[i] = i + 1;
            for (int i = l; i < n; ++i)
                friendRegion[i] = rnd.next(1, l);
            shuffle(friendRegion.begin(), friendRegion.end());
        } else if (friendDistType == 1) {
            // Skewed toward a main region
            int mainRegion = rnd.next(1, l);
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 99) < 70)
                    friendRegion[i] = mainRegion;
                else
                    friendRegion[i] = rnd.next(1, l);
            }
        } else {
            // Completely random regions
            for (int i = 0; i < n; ++i)
                friendRegion[i] = rnd.next(1, l);
        }

        // Drunk/sober status
        vector<char> status(n, 'I');
        if (drunkPattern == 0) {
            // All sober
            for (int i = 0; i < n; ++i) status[i] = 'S';
        } else if (drunkPattern == 1) {
            // All drunk (no driver anywhere)
            for (int i = 0; i < n; ++i) status[i] = 'I';
        } else if (drunkPattern == 2) {
            // At least one sober per region (if region has friends)
            for (int i = 0; i < n; ++i) status[i] = 'I';
            for (int r = 1; r <= l; ++r) {
                vector<int> idx;
                for (int i = 0; i < n; ++i)
                    if (friendRegion[i] == r)
                        idx.push_back(i);
                if (!idx.empty()) {
                    int chosen = rnd.any(idx);
                    status[chosen] = 'S';
                }
            }
            // Additional random sobers
            for (int i = 0; i < n; ++i)
                if (status[i] == 'I' && rnd.next(0, 99) < 30)
                    status[i] = 'S';
        } else if (drunkPattern == 3) {
            // Mostly drunk but at least one sober globally
            bool hasSober = false;
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 99) < 20) {
                    status[i] = 'S';
                    hasSober = true;
                } else {
                    status[i] = 'I';
                }
            }
            if (!hasSober) {
                int idx = rnd.next(0, n - 1);
                status[idx] = 'S';
            }
        } else if (drunkPattern == 4) {
            // Mostly sober but at least one drunk globally
            bool hasDrunk = false;
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 99) < 80) {
                    status[i] = 'S';
                } else {
                    status[i] = 'I';
                    hasDrunk = true;
                }
            }
            if (!hasDrunk) {
                int idx = rnd.next(0, n - 1);
                status[idx] = 'I';
            }
        } else {
            // Mixed, random ~50-50
            for (int i = 0; i < n; ++i) {
                status[i] = (rnd.next(0, 1) == 0 ? 'I' : 'S');
            }
        }

        // Output friends
        for (int i = 0; i < n; ++i)
            println(friendRegion[i], status[i]);

        // ----- Generate cars -----
        vector<int> carRegion(c);
        vector<int> carCap(c);

        // Region distribution for cars
        if (carDistType == 0) {
            // Balanced: at least one car per region
            for (int i = 0; i < l; ++i)
                carRegion[i] = i + 1;
            for (int i = l; i < c; ++i)
                carRegion[i] = rnd.next(1, l);
            shuffle(carRegion.begin(), carRegion.end());
        } else if (carDistType == 1) {
            // Skewed: many cars for one region
            int mainRegion = rnd.next(1, l);
            for (int i = 0; i < c; ++i) {
                if (rnd.next(0, 99) < 70)
                    carRegion[i] = mainRegion;
                else
                    carRegion[i] = rnd.next(1, l);
            }
        } else {
            // Random
            for (int i = 0; i < c; ++i)
                carRegion[i] = rnd.next(1, l);
        }

        // Capacities
        for (int i = 0; i < c; ++i) {
            if (capPattern == 0) {
                // Small capacities
                carCap[i] = rnd.next(2, 4);
            } else if (capPattern == 1) {
                // Larger capacities
                carCap[i] = rnd.next(5, 8);
            } else {
                // Mixed
                carCap[i] = rnd.next(2, 8);
            }
        }

        // Output cars
        for (int i = 0; i < c; ++i)
            println(carRegion[i], carCap[i]);
    }

    return 0;
}
