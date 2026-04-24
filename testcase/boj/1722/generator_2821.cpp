#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of permutation
    int N = rnd.next(1, 10);

    // Precompute factorials up to N
    vector<int> fact(N + 1);
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i;
    }

    // Choose which subproblem: 1 (kth permutation) or 2 (rank of permutation)
    int typ = rnd.next(1, 2);

    // Output N
    println(N);

    if (typ == 1) {
        // Subproblem 1: generate k in [1, N!], with skew options
        int skew = rnd.next(-1, 1);
        int k;
        if (skew == 0) {
            // uniform
            k = rnd.next(1, fact[N]);
        } else {
            // weighted toward high (skew>0) or low (skew<0)
            k = rnd.wnext(fact[N], skew) + 1;  // rnd.wnext gives [0, fact[N]-1]
        }
        // print "1 k"
        println(1, k);
    } else {
        // Subproblem 2: generate a permutation
        vector<int> p(N);
        iota(p.begin(), p.end(), 1);
        // sometimes sorted, sometimes reversed, else random
        int mode = rnd.next(0, 9);
        if (mode == 0) {
            // already sorted
        } else if (mode == 1) {
            reverse(p.begin(), p.end());
        } else {
            shuffle(p.begin(), p.end());
        }
        // print "2 p1 p2 ... pN"
        vector<int> out;
        out.push_back(2);
        out.insert(out.end(), p.begin(), p.end());
        println(out);
    }

    return 0;
}
