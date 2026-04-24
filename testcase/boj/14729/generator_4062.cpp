#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students: small for hand-check
    int N = rnd.next(8, 20);

    // Choose distribution type for diversity
    int distType = rnd.next(0, 3);

    vector<int> scores;
    scores.reserve(N);

    if (distType == 0) {
        // Uniform distribution over [0, 100.000]
        for (int i = 0; i < N; i++) {
            scores.push_back(rnd.next(0, 100000));
        }
    }
    else if (distType == 1) {
        // Clustered low: 70% in [0,20], others uniform
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.7)
                scores.push_back(rnd.next(0, 20000));
            else
                scores.push_back(rnd.next(0, 100000));
        }
    }
    else if (distType == 2) {
        // Clustered high: 70% in [80,100], others uniform
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.7)
                scores.push_back(rnd.next(80000, 100000));
            else
                scores.push_back(rnd.next(0, 100000));
        }
    }
    else {
        // Many duplicates: pick a small set of K distinct values
        int K = rnd.next(7, 10);
        set<int> st;
        while ((int)st.size() < K) {
            st.insert(rnd.next(0, 100000));
        }
        vector<int> vals(st.begin(), st.end());
        for (int i = 0; i < N; i++) {
            scores.push_back(rnd.any(vals));
        }
    }

    // Shuffle to make input unsorted
    shuffle(scores.begin(), scores.end());

    // Output
    println(N);
    for (int x : scores) {
        // Print with exactly 3 decimals
        int whole = x / 1000;
        int frac = x % 1000;
        printf("%d.%03d\n", whole, frac);
    }

    return 0;
}
