#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for K: sometimes 1, power of two, small, or large
    int ktype = rnd.next(0, 3);
    int K;
    if (ktype == 0) {
        K = 1;
    } else if (ktype == 1) {
        int e = rnd.next(0, 13);
        K = 1 << e;
        if (K > 10000) K = K >> 1;
    } else if (ktype == 2) {
        K = rnd.next(2, 100);
    } else {
        K = rnd.next(500, 10000);
    }
    // Hyper-parameter for T: small, medium, or larger
    int ttype = rnd.next(0, 2);
    int T;
    if (ttype == 0) {
        T = rnd.next(1, 5);
    } else if (ttype == 1) {
        T = rnd.next(6, 15);
    } else {
        T = rnd.next(16, 20);
    }
    // Generate N_i with varied scales
    vector<long long> Ns;
    for (int i = 0; i < T; i++) {
        int ntype = rnd.next(0, 3);
        long long N;
        if (ntype == 0) {
            N = 1;  // edge
        } else if (ntype == 1) {
            N = rnd.next(2LL, 20LL);  // small
        } else if (ntype == 2) {
            N = rnd.next(21LL, 100000LL);  // medium
        } else {
            // large: occasionally exactly 1e10, else random in big ranges
            if (rnd.next(0, 4) == 0) {
                N = 10000000000LL;
            } else if (rnd.next(0, 1) == 0) {
                N = rnd.next(100001LL, 1000000LL);
            } else {
                N = rnd.next(1000001LL, 10000000000LL);
            }
        }
        Ns.push_back(N);
    }
    // Shuffle test-case order for variability
    shuffle(Ns.begin(), Ns.end());
    // Output
    println(K, T);
    for (long long N : Ns) {
        println(N);
    }
    return 0;
}
