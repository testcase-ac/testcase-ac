#include "testlib.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand-checkable input
    int N = rnd.next(2, 10);

    vector<int> candidates = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(candidates.begin(), candidates.end());
    candidates.resize(rnd.wnext(9, 1) + 1);

    double sticky_prob = rnd.next(0.0, 0.7);
    // Generate fruit types (1–9) with occasional bias
    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        if(i && rnd.next() < sticky_prob) {
            S[i] = S[i-1];
        } else {
            S[i] = rnd.any(candidates);
        }
    }


    // Output N and the sequence
    println(N);
    for (int i = 0; i < N; ++i) {
        printf("%d%c", S[i], (i + 1 == N) ? '\n' : ' ');
    }

    return 0;
}
