#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);
    int Q = rnd.next(1, 10);

    // Generate the novel sequence with diverse patterns
    vector<int> seq(N);
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // Uniform random
        for (int i = 0; i < N; i++)
            seq[i] = rnd.next(1, M);
    } else if (pattern == 1) {
        // Sorted ascending
        for (int i = 0; i < N; i++)
            seq[i] = rnd.next(1, M);
        sort(seq.begin(), seq.end());
    } else if (pattern == 2) {
        // Sorted descending
        for (int i = 0; i < N; i++)
            seq[i] = rnd.next(1, M);
        sort(seq.begin(), seq.end(), greater<int>());
    } else {
        // Repetition patterns
        if (M == 1 || rnd.next(0, 1) == 0) {
            // All same
            int x = rnd.next(1, M);
            for (int i = 0; i < N; i++)
                seq[i] = x;
        } else {
            // Exactly two distinct values
            int x = rnd.next(1, M);
            int y = rnd.next(1, M);
            while (y == x) y = rnd.next(1, M);
            for (int i = 0; i < N; i++)
                seq[i] = (rnd.next(0, 1) ? x : y);
        }
    }
    // Optional shuffle to break order
    if (rnd.next(0, 1))
        shuffle(seq.begin(), seq.end());

    // Generate queries for K with varied distributions (all within [1, M^2])
    int maxK = M * M;
    vector<int> Ks(Q);
    for (int i = 0; i < Q; i++) {
        int t = rnd.next(0, 2);
        if (t == 0) {
            // Small K
            int up = min(5, maxK);
            Ks[i] = rnd.next(1, up);
        } else if (t == 1) {
            // Uniform over full range
            Ks[i] = rnd.next(1, maxK);
        } else {
            // Bias towards large values
            Ks[i] = rnd.wnext(maxK, 2) + 1;
        }
    }

    // Output the generated test case
    println(N, M, Q);
    println(seq);
    for (int k : Ks)
        println(k);

    return 0;
}
