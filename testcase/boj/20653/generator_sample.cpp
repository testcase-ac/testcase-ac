#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int smallMultiplier() {
    vector<int> values = {
        1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 16, 18, 24, 30, 36, 60, 72, 120
    };
    return rnd.any(values);
}

int chooseN() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.next(2, 6);
    if (mode == 1) return rnd.next(7, 30);
    if (mode == 2) return rnd.next(100, 1000);
    if (mode == 3) return rnd.next(999990, 1000000);
    return rnd.next(2, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 20);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int n = chooseN();
        int mode = rnd.next(0, 5);
        int G = 1;
        int L = 1;

        if (mode == 0) {
            G = rnd.next(1, 1000);
            L = G;
        } else if (mode == 1) {
            int mult = smallMultiplier();
            G = rnd.next(1, 1000000000 / mult);
            L = G * mult;
        } else if (mode == 2) {
            vector<int> largeL = {999999937, 999999996, 1000000000};
            L = rnd.any(largeL);
            vector<int> divisors;
            for (int d = 1; d <= 100000 && d <= L; ++d) {
                if (L % d == 0) divisors.push_back(d);
            }
            G = rnd.any(divisors);
        } else if (mode == 3) {
            G = rnd.next(2, 1000000000);
            L = rnd.next(1, G - 1);
        } else if (mode == 4) {
            G = rnd.next(2, 100000);
            int maxQ = min(10000, (1000000000 - (G - 1)) / G);
            L = G * rnd.next(1, maxQ) + rnd.next(1, G - 1);
        } else {
            G = rnd.next(1, 1000000000);
            L = rnd.next(1, 1000000000);
        }

        println(n, G, L);
    }

    return 0;
}
