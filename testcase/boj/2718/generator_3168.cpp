#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Maximum N such that tilings <= 2^31-1 is 21
    const int maxN = 21;
    // Number of test cases
    int T = rnd.next(1, 10);
    vector<int> Ns;
    // Generate with three categories: small, medium, large
    for (int i = 0; i < T; i++) {
        double r = rnd.next();  // in [0,1)
        int n;
        if (r < 0.3) {
            n = rnd.next(1, 5);
        } else if (r < 0.7) {
            n = rnd.next(6, 15);
        } else {
            n = rnd.next(16, maxN);
        }
        Ns.push_back(n);
    }
    // Ensure we have both 1 and maxN at least once if T>=2
    if (T >= 2) {
        bool has1 = false, hasMax = false;
        for (int x : Ns) {
            if (x == 1) has1 = true;
            if (x == maxN) hasMax = true;
        }
        if (!has1) Ns.push_back(1);
        if (!hasMax) Ns.push_back(maxN);
        // Trim back to T by removing random extras
        while ((int)Ns.size() > T) {
            int idx = rnd.next((int)Ns.size());
            Ns.erase(Ns.begin() + idx);
        }
    }
    // Shuffle the order of test cases
    shuffle(Ns.begin(), Ns.end());
    // Output
    println(T);
    for (int n : Ns) {
        println(n);
    }
    return 0;
}
