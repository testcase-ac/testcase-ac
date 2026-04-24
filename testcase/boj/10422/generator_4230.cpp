#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);
    // Special interesting L values
    vector<int> special = {1, 2, 3, 4, 4999, 5000};
    for (int i = 0; i < T; i++) {
        int L;
        // 20% chance to pick a special boundary value
        if (rnd.next() < 0.2) {
            L = rnd.any(special);
        } else {
            // Decide desired parity: even or odd
            bool wantEven = rnd.next() < 0.5;
            // 70% small, 30% large
            int hi = (rnd.next() < 0.7 ? 20 : 5000);
            int k = rnd.next(1, hi);
            // Adjust parity if needed
            if (wantEven) {
                if (k % 2 != 0) {
                    if (k < hi) k++;
                    else k--;
                }
            } else {
                if (k % 2 == 0) {
                    if (k < hi) k++;
                    else k--;
                }
            }
            L = k;
        }
        // Output L
        println(L);
    }
    return 0;
}
