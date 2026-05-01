#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N up to 30 for hand-verifiable size
    int N = rnd.next(1, 30);
    int mode = rnd.next(0, 2); // 0: no valid window, 1: general, 2: exactly K ones

    int K;
    vector<int> a(N, 2);

    if (mode == 0) {
        // Guarantee no valid window: total ones < K
        K = rnd.next(1, N);
        int cnt = (K > 1 ? rnd.next(0, K - 1) : 0);
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < cnt; i++) {
            a[idx[i]] = 1;
        }
    } else if (mode == 2) {
        // Exactly K ones in total
        K = rnd.next(1, N);
        int cnt = K;
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < cnt; i++) {
            a[idx[i]] = 1;
        }
    } else {
        // General case: total ones >= K
        K = rnd.next(1, N);
        int cnt = rnd.next(K, N);
        bool cluster = rnd.next(0, 1) == 0;
        if (cluster) {
            // Place ones in one contiguous block
            int start = rnd.next(0, N - cnt);
            for (int i = start; i < start + cnt; i++) {
                a[i] = 1;
            }
        } else {
            // Spread ones randomly
            vector<int> idx(N);
            iota(idx.begin(), idx.end(), 0);
            shuffle(idx.begin(), idx.end());
            for (int i = 0; i < cnt; i++) {
                a[idx[i]] = 1;
            }
        }
    }

    // Output
    println(N, K);
    println(a);
    return 0;
}
