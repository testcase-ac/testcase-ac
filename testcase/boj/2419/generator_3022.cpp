#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // number of baskets
    int n = rnd.next(0, 10);
    // initial candies: either small or full range
    int m = (rnd.next(0, 1) ? rnd.next(1, 1000) : rnd.next(1, 1000000));
    println(n, m);

    if (n > 0) {
        vector<int> xs;
        int type = rnd.next(0, 2);
        if (type == 0) {
            // symmetric around zero
            int need = n;
            if (need % 2 == 1) {
                xs.push_back(0);
                --need;
            }
            int half = need / 2;
            int maxAbs = rnd.next(1, 10000);
            set<int> used;
            while ((int)used.size() < half) {
                used.insert(rnd.next(1, maxAbs));
            }
            for (int v : used) {
                xs.push_back(v);
                xs.push_back(-v);
            }
        } else if (type == 1) {
            // clustered around a random center
            int center = rnd.next(-1000, 1000);
            set<int> used;
            while ((int)used.size() < n) {
                used.insert(center + rnd.next(-50, 50));
            }
            xs.assign(used.begin(), used.end());
        } else {
            // fully random
            set<int> used;
            while ((int)used.size() < n) {
                used.insert(rnd.next(-10000, 10000));
            }
            xs.assign(used.begin(), used.end());
        }
        shuffle(xs.begin(), xs.end());
        for (int v : xs) println(v);
    }

    return 0;
}
