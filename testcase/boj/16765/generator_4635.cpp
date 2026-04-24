#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cows
    int N = rnd.next(2, 10);
    // Team max size K, skewed by wnext
    vector<int> tvals = {-1, 0, 1};
    int t = rnd.any(tvals);
    int K = rnd.wnext(N, t) + 1;  // in [1..N]
    // Skill distribution upper bound, skewed
    int t2 = rnd.any(tvals);
    int maxSkill = rnd.wnext(100, t2) + 1;  // in [1..100]
    // Generate raw skills
    vector<int> s(N);
    for (int i = 0; i < N; i++) {
        s[i] = rnd.next(1, maxSkill);
    }
    // Occasionally make monotonic to test edge patterns
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        sort(s.begin(), s.end());
    } else if (mode == 1) {
        sort(s.begin(), s.end(), greater<int>());
    }
    // Occasionally introduce repeated clusters
    if (rnd.next(0, 2) == 0) {
        for (int i = 1; i < N; i++) {
            if (rnd.next(0, N - 1) < N / 4) {
                s[i] = s[i - 1];
            }
        }
    }
    // Output
    println(N, K);
    for (int x : s) println(x);
    return 0;
}
