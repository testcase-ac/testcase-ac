#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in a few size classes for variability but keep it small/readable
    int sizeClass = rnd.next(0, 2); // 0: small, 1: medium, 2: larger
    int N;
    if (sizeClass == 0) N = rnd.next(1, 5);
    else if (sizeClass == 1) N = rnd.next(6, 15);
    else N = rnd.next(16, 30);

    // Choose a pattern type for the permutation
    int patternType = rnd.next(0, 7);

    vector<int> p(N);

    if (patternType == 0) {
        // Identity: already sorted
        for (int i = 0; i < N; i++) p[i] = i + 1;
    } else if (patternType == 1) {
        // Fully reversed
        for (int i = 0; i < N; i++) p[i] = N - i;
    } else if (patternType == 2) {
        // Completely random permutation
        for (int i = 0; i < N; i++) p[i] = i + 1;
        shuffle(p.begin(), p.end());
    } else if (patternType == 3) {
        // One large at the front, rest increasing
        for (int i = 0; i < N; i++) p[i] = i + 1;
        if (N >= 2) {
            swap(p[0], p[N - 1]); // put N at front
        }
    } else if (patternType == 4) {
        // Alternating high/low pattern: N,1,N-1,2,...
        int lo = 1, hi = N, idx = 0;
        while (lo <= hi) {
            if (idx < N) p[idx++] = hi--;
            if (idx < N) p[idx++] = lo++;
        }
    } else if (patternType == 5) {
        // Two sorted blocks: big numbers first, then small ones
        if (N == 1) {
            p[0] = 1;
        } else {
            int k = rnd.next(1, N - 1); // split point
            int idx = 0;
            for (int x = k + 1; x <= N; x++) p[idx++] = x;
            for (int x = 1; x <= k; x++) p[idx++] = x;
        }
    } else if (patternType == 6) {
        // Nearly sorted: start sorted, perform few random swaps
        for (int i = 0; i < N; i++) p[i] = i + 1;
        int swaps = (N <= 2) ? 1 : rnd.next(1, max(1, N / 3));
        for (int s = 0; s < swaps; s++) {
            if (N >= 2 && rnd.next(0, 1) == 0) {
                // Adjacent swap
                int i = rnd.next(0, N - 2);
                swap(p[i], p[i + 1]);
            } else {
                // Any two positions
                int i = rnd.next(0, N - 1);
                int j = rnd.next(0, N - 1);
                if (i != j) swap(p[i], p[j]);
            }
        }
    } else {
        // patternType == 7
        // Long increasing prefix, random/decreasing suffix
        if (N == 1) {
            p[0] = 1;
        } else {
            int L = rnd.next(max(1, N / 2), N - 1); // length of increasing prefix
            for (int i = 0; i < L; i++) p[i] = i + 1;
            vector<int> tail;
            for (int v = L + 1; v <= N; v++) tail.push_back(v);
            if (!tail.empty()) {
                if (rnd.next(0, 1) == 0) {
                    reverse(tail.begin(), tail.end());
                } else {
                    shuffle(tail.begin(), tail.end());
                }
                for (int i = 0; i < (int)tail.size(); i++) {
                    p[L + i] = tail[i];
                }
            }
        }
    }

    // Output the test case
    println(N);
    println(p);

    return 0;
}
