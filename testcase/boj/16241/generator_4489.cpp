#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checking
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Hyper-parameters: cluster counts for diversity
    int maxClL = min(N, rnd.next(1, 3));
    int maxClR = min(M, rnd.next(1, 3));

    // Split counts into clusters
    vector<int> cntL(maxClL, 1), cntR(maxClR, 1);
    int remL = N - maxClL;
    while (remL-- > 0) {
        cntL[rnd.next(0, maxClL - 1)]++;
    }
    int remR = M - maxClR;
    while (remR-- > 0) {
        cntR[rnd.next(0, maxClR - 1)]++;
    }

    // Pick cluster centers and noise
    vector<int> centersL(maxClL), centersR(maxClR);
    int maxCenter = 100;
    for (int i = 0; i < maxClL; i++) {
        centersL[i] = rnd.next(1, maxCenter);
    }
    for (int i = 0; i < maxClR; i++) {
        centersR[i] = rnd.next(1, maxCenter);
    }
    int noiseL = rnd.next(0, 20);
    int noiseR = rnd.next(0, 20);

    // Generate shoe sizes
    vector<int> L, R;
    for (int i = 0; i < maxClL; i++) {
        int lo = max(1, centersL[i] - noiseL);
        int hi = centersL[i] + noiseL;
        for (int j = 0; j < cntL[i]; j++) {
            L.push_back(rnd.next(lo, hi));
        }
    }
    for (int i = 0; i < maxClR; i++) {
        int lo = max(1, centersR[i] - noiseR);
        int hi = centersR[i] + noiseR;
        for (int j = 0; j < cntR[i]; j++) {
            R.push_back(rnd.next(lo, hi));
        }
    }

    // Optional special patterns: duplicates or wide spread
    if (rnd.next(0, 9) == 0) {
        // all left same
        int val = rnd.next(1, maxCenter);
        for (int &x : L) x = val;
    }
    if (rnd.next(0, 9) == 0) {
        // all right same
        int val = rnd.next(1, maxCenter);
        for (int &x : R) x = val;
    }

    // Shuffle or sort patterns
    int pat = rnd.next(0, 2);
    if (pat == 0) {
        shuffle(L.begin(), L.end());
        shuffle(R.begin(), R.end());
    } else if (pat == 1) {
        sort(L.begin(), L.end());
        sort(R.begin(), R.end());
    } else {
        sort(L.begin(), L.end());
        sort(R.begin(), R.end());
        reverse(L.begin(), L.end());
        reverse(R.begin(), R.end());
    }

    // Output
    println(N, M);
    println(L);
    println(R);

    return 0;
}
