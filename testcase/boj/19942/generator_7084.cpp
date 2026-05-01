#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of ingredients
    int N = rnd.next(3, 15);
    vector<int> p(N), f(N), s(N), v(N), c(N);
    // Generate ingredients with varied nutrition profiles
    for (int i = 0; i < N; i++) {
        // Weighted randomness: some ingredients are rich, some are poor
        int wt = rnd.next(-1, 1);
        p[i] = rnd.wnext(101, wt);
        f[i] = rnd.wnext(101, wt);
        s[i] = rnd.wnext(101, wt);
        v[i] = rnd.wnext(101, wt);
        // Cost between 1 and 100
        c[i] = rnd.next(1, 100);
    }
    // Pick a random non-empty subset S that has some nutrition
    vector<int> idx(N), S;
    iota(idx.begin(), idx.end(), 0);
    vector<int> sum(4);
    do {
        shuffle(idx.begin(), idx.end());
        int k = rnd.next(1, N);
        S.assign(idx.begin(), idx.begin() + k);
        sum = {0, 0, 0, 0};
        for (int x : S) {
            sum[0] += p[x];
            sum[1] += f[x];
            sum[2] += s[x];
            sum[3] += v[x];
        }
    } while (sum[0] + sum[1] + sum[2] + sum[3] == 0);

    // Build thresholds mp, mf, ms, mv so that subset S meets them
    vector<int> mp(4);
    for (int d = 0; d < 4; d++) {
        int high = min(sum[d], 500);
        int lo = rnd.next(0, high);
        mp[d] = rnd.next(lo, high);
    }
    // Ensure at least one threshold > 0
    if (mp[0] + mp[1] + mp[2] + mp[3] == 0) {
        vector<int> pos;
        for (int d = 0; d < 4; d++)
            if (sum[d] > 0) pos.push_back(d);
        int d = rnd.any(pos);
        int high = min(sum[d], 500);
        mp[d] = rnd.next(1, high);
    }

    // Output
    println(N);
    println(mp);
    for (int i = 0; i < N; i++) {
        printf("%d %d %d %d %d\n", p[i], f[i], s[i], v[i], c[i]);
    }
    return 0;
}
