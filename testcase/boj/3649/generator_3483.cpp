#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 5);
    for (int ti = 0; ti < T; ti++) {
        // Hole width in cm
        int x = rnd.next(1, 20);
        long long S = 1LL * x * 10000000; // target sum in nanometers

        // Decide if this case should have a valid pair or be "danger"
        bool wantValid = rnd.next(0, 1) == 1;

        // Number of blocks (small for hand-checking)
        int n = rnd.next(0, 10);
        if (wantValid && n < 2) n = 2;

        vector<int> v;
        // If valid, insert exactly one matching pair
        if (wantValid) {
            long long lo = max(1LL, S - 100000000LL);
            long long hi = min(100000000LL, S - 1);
            int a = rnd.next((int)lo, (int)hi);
            int b = (int)(S - a);
            v.push_back(a);
            v.push_back(b);
        }

        // Fill the rest with random lengths that do not create any extra sum == S
        while ((int)v.size() < n) {
            int r = rnd.next(1, 100000000);
            bool ok = true;
            for (int u : v) {
                if ((long long)u + r == S) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                v.push_back(r);
            }
        }

        // Output this test case
        println(x);
        println(n);
        for (int u : v) {
            println(u);
        }
    }

    return 0;
}
