#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Choose number of slimes
        int N = rnd.next(1, 10);
        // Choose upper bound for slime energy
        int boundMax = rnd.any(vector<int>{10, 50});
        // Mode: uniform or varied energies
        int mode = rnd.next(1, 2);
        vector<long long> C(N);
        if (mode == 1) {
            // All slimes have the same energy
            long long x = rnd.next(2LL, (long long)boundMax);
            for (int i = 0; i < N; i++) C[i] = x;
        } else {
            // Each slime energy random
            for (int i = 0; i < N; i++)
                C[i] = rnd.next(2LL, (long long)boundMax);
        }
        // Shuffle input order for diversity
        shuffle(C.begin(), C.end());
        println(N);
        println(C);
    }
    return 0;
}
