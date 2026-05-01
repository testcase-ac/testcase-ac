#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N: mostly small, occasionally medium
    double p = rnd.next();
    int N = (p < 0.2 ? rnd.next(50, 100) : rnd.next(1, 20));

    vector<long long> S(N);
    int type = rnd.next(0, 4);
    const long long MAXV = 2147483647LL;

    if (type == 0) {
        // pure random in [0, mx]
        int mx = rnd.next(0, 1000);
        for (int i = 0; i < N; i++)
            S[i] = rnd.next(0, mx);
        shuffle(S.begin(), S.end());
    }
    else if (type == 1) {
        // sorted ascending
        for (int i = 0; i < N; i++)
            S[i] = rnd.next(0, 1000);
        sort(S.begin(), S.end());
    }
    else if (type == 2) {
        // sorted descending
        for (int i = 0; i < N; i++)
            S[i] = rnd.next(0, 1000);
        sort(S.begin(), S.end(), greater<long long>());
    }
    else if (type == 3) {
        // many duplicates
        int k = rnd.next(1, min(N, 5));
        vector<long long> pool(k);
        for (int i = 0; i < k; i++)
            pool[i] = rnd.next(0, 10);
        for (int i = 0; i < N; i++)
            S[i] = rnd.any(pool);
        shuffle(S.begin(), S.end());
    }
    else {
        // extreme values
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) S[i] = 0;
            else S[i] = MAXV;
        }
        if (N % 2 == 1) {
            // replace one element with random mid-value
            int idx = rnd.next(0, N - 1);
            S[idx] = rnd.next(1LL, MAXV - 1);
        }
        shuffle(S.begin(), S.end());
    }

    // Output
    println(N);
    println(S);

    return 0;
}
