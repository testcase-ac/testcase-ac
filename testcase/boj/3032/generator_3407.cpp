#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size N
    int N = rnd.next(1, 10);

    vector<int> a;
    set<int> used;

    if (N == 1) {
        // Single element case
        int x = rnd.next(1, 1000);
        a.push_back(x);
    } else {
        // Hyper-parameter: choose a pattern for parity distribution
        // 0 = fully random, 1 = alternating parity,
        // 2 = block of odds then evens, 3 = exactly one odd
        int type = rnd.next(0, 3);
        int par0 = 0, k = 0, pos = 0;
        if (type == 1) {
            par0 = rnd.next(0, 1); // starting parity for alternating
        } else if (type == 2) {
            k = rnd.next(1, N - 1); // number of odds in front
        } else if (type == 3) {
            pos = rnd.next(0, N - 1); // position of the single odd
        }

        for (int i = 0; i < N; i++) {
            int want_parity = -1;
            if (type == 1) {
                want_parity = par0 ^ (i % 2);
            } else if (type == 2) {
                want_parity = (i < k ? 1 : 0);
            } else if (type == 3) {
                want_parity = (i == pos ? 1 : 0);
            }
            // Generate a distinct number matching desired parity (if any)
            int x;
            do {
                x = rnd.next(1, 1000);
            } while (used.count(x) || (want_parity >= 0 && (x % 2) != want_parity));
            a.push_back(x);
            used.insert(x);
        }
    }

    // Output the test case
    println(N);
    println(a);

    return 0;
}
