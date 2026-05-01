#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Pick N modestly small for manual verification
    int N = rnd.next(3, 30);
    int maxM = (N + 1) / 2;
    // Choose M: sometimes edge 1, sometimes max, else random
    double p = rnd.next();
    int M;
    if (p < 0.2) M = 1;
    else if (p < 0.4) M = maxM;
    else M = rnd.next(1, maxM);
    // Choose maximum strength value
    int maxV = rnd.any(vector<int>{10, 100, 1000});
    // Generate array with various patterns
    vector<int> a(N);
    int pattern = rnd.next(0, 4);
    if (pattern == 0) {
        // fully random
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, maxV);
    } else if (pattern == 1) {
        // increasing with small noise
        int base = rnd.next(0, maxV/4);
        for (int i = 0; i < N; i++)
            a[i] = min(maxV, base + i * rnd.next(1, 3) + rnd.next(0, 5) + 1);
    } else if (pattern == 2) {
        // decreasing with noise
        int base = rnd.next(0, maxV/4);
        for (int i = 0; i < N; i++)
            a[i] = min(maxV, base + (N - i) * rnd.next(1, 3) + rnd.next(0, 5) + 1);
    } else if (pattern == 3) {
        // plateaus: small constant blocks
        int i = 0;
        while (i < N) {
            int len = rnd.next(1, 3);
            int v = rnd.next(1, maxV);
            for (int j = 0; j < len && i < N; j++, i++)
                a[i] = v;
        }
    } else {
        // zigzag high/low
        int high = maxV;
        int low = max(1, maxV/10);
        for (int i = 0; i < N; i++)
            a[i] = (i % 2 == 0 ? high : low) + rnd.next(0, rnd.next(0, 5));
    }
    // Occasionally insert a single peak or valley
    if (rnd.next() < 0.3) {
        int pos = rnd.next(0, N-1);
        a[pos] = rnd.next(1, maxV);
    }
    // Output
    println(N, M);
    println(a);
    return 0;
}
