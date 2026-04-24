#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: number of questions
    int N = rnd.next(1, 10);
    // Hyper-parameter: maximum individual score base
    int baseMax = rnd.any(vector<int>{10, 100});
    // Generate raw scores
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        S[i] = rnd.next(1, baseMax);
    }
    // Trend: 0=random, 1=increasing, 2=decreasing
    int trend = rnd.next(0, 2);
    if (trend == 1) {
        sort(S.begin(), S.end());
    } else if (trend == 2) {
        sort(S.begin(), S.end(), greater<int>());
    }
    // Compute maximum possible total score
    vector<int> pref(N);
    pref[0] = S[0];
    for (int i = 1; i < N; i++) {
        pref[i] = pref[i-1] + S[i];
    }
    long long maxScore = 0;
    for (int i = 0; i < N; i++) {
        maxScore += pref[i];
    }
    // Choose K with diverse distributions
    double r = rnd.next();
    int K;
    if (r < 0.5) {
        // Somewhere within achievable range
        K = rnd.next(1, (int)maxScore);
    } else if (r < 0.8) {
        // Just above achievable
        K = rnd.next((int)maxScore + 1, (int)maxScore + 100);
    } else {
        // Well above achievable
        K = rnd.next((int)maxScore + 101, (int)maxScore + 1000);
    }
    // Output test case
    println(N);
    println(S);
    println(K);
    return 0;
}
