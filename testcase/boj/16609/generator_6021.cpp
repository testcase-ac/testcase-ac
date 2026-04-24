#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of balloons/canisters
    int n = rnd.next(1, 12);
    vector<int> c(n);
    // Decide to force an impossible case in some runs (only if n>=2)
    bool wantImpossible = (n >= 2) && (rnd.next(0, 3) == 0);
    if (wantImpossible) {
        // Force at least two largest canisters that will overflow the smaller balloon
        c[0] = n;
        c[1] = n;
        for (int i = 2; i < n; i++) {
            c[i] = rnd.next(0, n);
        }
    } else {
        // Generate a guaranteed-feasible assignment:
        // After sorting c descending and sizes descending (n, n-1, ...,1),
        // enforce c_sorted[i] <= size_sorted[i] = n - i.
        vector<int> cap_desc(n);
        for (int i = 0; i < n; i++) {
            cap_desc[i] = n - i;
        }
        vector<int> sorted_c(n);
        for (int i = 0; i < n; i++) {
            sorted_c[i] = rnd.next(0, cap_desc[i]);
        }
        shuffle(sorted_c.begin(), sorted_c.end());
        c = sorted_c;
    }
    // Output
    println(n);
    println(c);
    return 0;
}
