#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small N and Q for hand verification, with variability
    int N = rnd.next(1, 12);
    int Q = rnd.next(1, 12);
    // Generate initial A with segments to create equal, increasing, decreasing patterns
    vector<int> A(N+1);
    int curr = rnd.next(1, 10);
    A[1] = curr;
    int pos = 2;
    while (pos <= N) {
        int seg = rnd.next(1, min(4, N - pos + 1));
        int dir = rnd.next(0, 2);
        if (dir == 1) {
            curr += rnd.next(1, 3);
        } else if (dir == 2) {
            if (curr > 1) {
                int dmax = min(curr - 1, 3);
                curr -= rnd.next(1, dmax);
            }
        }
        if (curr < 1) curr = 1;
        if (curr > 10) curr = 10;
        for (int t = 0; t < seg && pos <= N; t++, pos++) {
            A[pos] = curr;
        }
    }
    // Decide number of type-2 queries (at least one)
    int k2 = rnd.next(1, Q);
    vector<bool> isType2(Q, false);
    for (int i = 0; i < k2; i++) isType2[i] = true;
    shuffle(isType2.begin(), isType2.end());
    // Output N, Q and initial A
    println(N, Q);
    vector<int> init(A.begin() + 1, A.end());
    println(init);
    // Generate queries
    for (int j = 0; j < Q; j++) {
        if (isType2[j]) {
            double p = rnd.next();
            int i;
            if (p < 0.3) i = 1;
            else if (p < 0.6) i = N;
            else i = rnd.next(1, N);
            println(2, i);
        } else {
            double p = rnd.next();
            int i;
            if (p < 0.3) i = 1;
            else if (p < 0.6) i = N;
            else i = rnd.next(1, N);
            // Choose x to test equal, increase, decrease, random
            double pe = rnd.next();
            int x;
            if (pe < 0.3) {
                x = A[i];
            } else if (pe < 0.6) {
                x = A[i] + rnd.next(1, 3);
            } else if (pe < 0.85 && A[i] > 1) {
                int dmax = min(A[i] - 1, 3);
                x = A[i] - rnd.next(1, dmax);
            } else {
                x = rnd.next(1, 10);
            }
            if (x < 1) x = 1;
            if (x > 10) x = 10;
            println(1, i, x);
            A[i] = x;
        }
    }
    return 0;
}
