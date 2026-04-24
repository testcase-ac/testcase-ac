#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand checking
    int N = rnd.next(1, 10);
    int M = rnd.next(1, N);

    // Hyper-parameters for day-amount distribution
    int lowBound = rnd.next(1, 200);
    int highBound = rnd.next(lowBound, 1000);
    int pattern = rnd.next(0, 2); // 0: uniform, 1: increasing trend, 2: peaks

    vector<int> days(N);
    if (pattern == 0) {
        // Uniformly random between lowBound and highBound
        for (int i = 0; i < N; i++) {
            days[i] = rnd.next(lowBound, highBound);
        }
    } else if (pattern == 1) {
        // Increasing trend: later days tend to be larger
        for (int i = 0; i < N; i++) {
            int minv = lowBound + i * (highBound - lowBound) / max(1, N - 1);
            days[i] = rnd.next(minv, highBound);
        }
    } else {
        // Few peaks among small values
        int peakCount = rnd.next(1, N);
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        // assign base small values
        for (int i = 0; i < N; i++) {
            days[i] = rnd.next(lowBound, lowBound + (highBound - lowBound) / 3);
        }
        // assign peaks
        for (int k = 0; k < peakCount; k++) {
            int i = idx[k];
            int lo = lowBound + 2*(highBound - lowBound)/3;
            days[i] = rnd.next(lo, highBound);
        }
    }

    // Output
    println(N, M);
    for (int x : days) println(x);

    return 0;
}
