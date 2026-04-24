#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N and valid K
    int N = rnd.next(3, 10);
    int K = rnd.next(0, N/2 - 1);

    // Decide distribution type
    int dist_type = rnd.next(0, 3);
    vector<int> scores(N);

    if (dist_type == 0) {
        // Uniform distribution over [0,10] with one decimal
        for (int i = 0; i < N; i++) {
            scores[i] = rnd.next(0, 100);
        }
    } else if (dist_type == 1) {
        // Clustered low scores: take minimum of 3 samples
        for (int i = 0; i < N; i++) {
            scores[i] = rnd.wnext(101, -2);
        }
    } else if (dist_type == 2) {
        // Clustered high scores: take maximum of 3 samples
        for (int i = 0; i < N; i++) {
            scores[i] = rnd.wnext(101, 2);
        }
    } else {
        // Few repeated values
        int rep_cnt = rnd.next(1, min(N, 3));
        vector<int> base;
        for (int i = 0; i < rep_cnt; i++) {
            base.push_back(rnd.next(0, 100));
        }
        for (int i = 0; i < N; i++) {
            scores[i] = rnd.any(base);
        }
    }

    // Shuffle so scores are in random order
    shuffle(scores.begin(), scores.end());

    // Output
    println(N, K);
    for (int x : scores) {
        printf("%.1f\n", x / 10.0);
    }

    return 0;
}
