#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N
    int N = rnd.next(2, 10);
    vector<int> counts(N);
    int total = 0;
    // Initial counts
    for (int i = 0; i < N; i++) {
        counts[i] = rnd.next(1, 5);
        total += counts[i];
    }
    // Number of commands
    int M = rnd.next(1, 15);
    // Output initial data
    println(N);
    // Print counts in one line
    if (N > 0) {
        printf("%d", counts[0]);
        for (int i = 1; i < N; i++) {
            printf(" %d", counts[i]);
        }
    }
    printf("\n");
    println(M);
    bool hasQuery = false;
    for (int cmd = 1; cmd <= M; cmd++) {
        int type;
        // Force at least one query by last command if none so far
        if (cmd == M && !hasQuery) {
            type = 2;
        } else {
            // If total==0 (shouldn't happen), force update
            if (total > 0)
                type = rnd.next(1, 2);
            else
                type = 1;
        }
        if (type == 1) {
            // Update: 1 i a
            int idx = rnd.next(1, N);
            bool doDec = false;
            if (total > 1)
                doDec = (rnd.next(0, 1) == 1);
            if (doDec && counts[idx-1] > 0) {
                int decMax = min(counts[idx-1], total - 1);
                if (decMax >= 1) {
                    int d = rnd.next(1, decMax);
                    counts[idx-1] -= d;
                    total -= d;
                    println(1, idx, -d);
                } else {
                    // fallback to increment
                    int inc = rnd.next(1, 5);
                    counts[idx-1] += inc;
                    total += inc;
                    println(1, idx, inc);
                }
            } else {
                int inc = rnd.next(1, 5);
                counts[idx-1] += inc;
                total += inc;
                println(1, idx, inc);
            }
        } else {
            // Query: 2 i
            int soldierId = rnd.next(1, total);
            println(2, soldierId);
            hasQuery = true;
        }
    }
    return 0;
}
