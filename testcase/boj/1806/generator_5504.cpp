#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for sequence length N in [10,50], skewed
    vector<int> tvals = {-1, 0, 1};
    int t = rnd.any(tvals);
    int N = 10 + rnd.wnext(41, t); // 10..50

    // Hyper-parameter for max element value
    int Amax = rnd.next(2, 10000);

    // Choose sequence pattern
    vector<int> pats = {0,1,2,3,4};
    int pat = rnd.any(pats);

    vector<int> a(N);
    int smallMax = max(1, Amax/10);
    int largeMin = smallMax + 1;

    // Generate sequence by pattern
    if (pat == 0) {
        // uniform random
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, Amax);
        }
    } else if (pat == 1) {
        // single spike
        int spikePos = rnd.next(0, N-1);
        for (int i = 0; i < N; i++) {
            if (i == spikePos)
                a[i] = rnd.next(largeMin, Amax);
            else
                a[i] = rnd.next(1, smallMax);
        }
    } else if (pat == 2) {
        // increasing
        for (int i = 0; i < N; i++) a[i] = rnd.next(1, Amax);
        sort(a.begin(), a.end());
    } else if (pat == 3) {
        // decreasing
        for (int i = 0; i < N; i++) a[i] = rnd.next(1, Amax);
        sort(a.begin(), a.end(), greater<int>());
    } else {
        // alternating small/large
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0)
                a[i] = rnd.next(1, smallMax);
            else
                a[i] = rnd.next(largeMin, Amax);
        }
    }

    // Compute total sum
    long long totalSum = 0;
    for (int v : a) totalSum += v;

    // Hyper-parameters for S
    long long highSmall = max(1LL, totalSum / 10);
    long long lowSmall = 1;
    long long lowMed = highSmall;
    long long highMed = max(lowMed, totalSum / 2);
    long long lowHuge = lowMed;
    long long highHuge = max(lowHuge, totalSum * 2);

    vector<int> smodes = {0,1,2};
    int mode = rnd.any(smodes);

    long long S;
    if (mode == 0) {
        S = rnd.next(lowSmall, highSmall);
    } else if (mode == 1) {
        S = rnd.next(lowMed, highMed);
    } else {
        S = rnd.next(lowHuge, highHuge);
    }

    // Output
    println(N, S);
    println(a);

    return 0;
}
