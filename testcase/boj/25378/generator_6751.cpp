#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with bias towards smaller sizes but occasionally uniform
    int N;
    if (rnd.next() < 0.7) {
        // weighted towards small: min of two samples from [0,18] + 2 => [2,20]
        N = rnd.wnext(19, -1) + 2;
    } else {
        N = rnd.next(2, 20);
    }
    // Choose a pattern to diversify cases
    int P = rnd.next(0, 4);
    vector<int> a(N);
    if (P == 0) {
        // Pure random heights, sometimes large
        int lb = rnd.next(1, 10);
        int ub = rnd.next(lb, 100);
        if (rnd.next() < 0.3) {
            lb = rnd.next(1, 1000);
            ub = rnd.next(lb, 100000000);
        }
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(lb, ub);
        }
    } else if (P == 1) {
        // All equal
        int c;
        if (rnd.next() < 0.3) c = rnd.next(1, 100000000);
        else c = rnd.next(1, 1000);
        for (int i = 0; i < N; i++) a[i] = c;
    } else if (P == 2) {
        // Increasing trend with small jitters
        int step = rnd.next(1, 50);
        for (int i = 0; i < N; i++) {
            int base = (i+1) * step;
            int jitter = rnd.next(0, step);
            a[i] = base + jitter;
        }
    } else if (P == 3) {
        // Mountain shape
        int peak = rnd.next(1, N);
        int step1 = rnd.next(1, 50);
        int step2 = rnd.next(1, 50);
        for (int i = 0; i < N; i++) {
            if (i+1 <= peak) {
                int base = (i+1) * step1;
                int jitter = rnd.next(0, step1);
                a[i] = base + jitter;
            } else {
                int idx = N - i;
                int base = idx * step2;
                int jitter = rnd.next(0, step2);
                a[i] = base + jitter;
            }
        }
    } else {
        // Piecewise constant runs
        int k = rnd.next(2, min(N, 4));
        vector<int> splits;
        while ((int)splits.size() < k-1) {
            int x = rnd.next(1, N-1);
            if (find(splits.begin(), splits.end(), x) == splits.end())
                splits.push_back(x);
        }
        sort(splits.begin(), splits.end());
        vector<int> bases(k);
        for (int j = 0; j < k; j++) {
            if (rnd.next() < 0.3) bases[j] = rnd.next(1, 1000000);
            else bases[j] = rnd.next(1, 100);
        }
        int p = 0;
        for (int i = 1; i <= N; i++) {
            if (p < (int)splits.size() && i > splits[p]) p++;
            a[i-1] = bases[p];
        }
    }
    // Output
    println(N);
    println(a);
    return 0;
}
