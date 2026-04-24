#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small N for hand-checkable
    int N = rnd.next(2, 10);

    // A and B small
    long long A = rnd.next(1, 20);
    long long len = rnd.next(0, 20);
    long long B = A + len;

    // C, D such that C + D < N
    int C, D;
    do {
        C = rnd.next(0, N - 1);
        D = rnd.next(0, N - 1);
    } while (C + D >= N);

    // Choose cycle structure type
    int type = rnd.next(0, 3);

    // Build permutation p of size N (1-based)
    vector<int> p(N + 1);
    for (int i = 1; i <= N; i++) p[i] = i;

    if (type == 0) {
        // identity: already set
    } else if (type == 1) {
        // single full cycle (rotation)
        for (int i = 1; i < N; i++) p[i] = i + 1;
        p[N] = 1;
    } else if (type == 2) {
        // completely random permutation
        vector<int> tmp(N);
        for (int i = 0; i < N; i++) tmp[i] = i + 1;
        shuffle(tmp.begin(), tmp.end());
        for (int i = 1; i <= N; i++) p[i] = tmp[i - 1];
    } else {
        // mix: some fixed points and one cycle on the rest
        vector<int> unfixed;
        for (int i = 1; i <= N; i++) {
            if (rnd.next(0, 1) == 0) {
                // fixed
                p[i] = i;
            } else {
                // to be in cycle
                unfixed.push_back(i);
            }
        }
        if ((int)unfixed.size() >= 2) {
            // make a single cycle among unfixed
            shuffle(unfixed.begin(), unfixed.end());
            int m = unfixed.size();
            for (int i = 0; i < m; i++) {
                int u = unfixed[i];
                int v = unfixed[(i + 1) % m];
                p[u] = v;
            }
        } else {
            // fallback to random
            vector<int> tmp(N);
            for (int i = 0; i < N; i++) tmp[i] = i + 1;
            shuffle(tmp.begin(), tmp.end());
            for (int i = 1; i <= N; i++) p[i] = tmp[i - 1];
        }
    }

    // Output in required format
    println(N, A, B, C, D);
    // print permutation P_1 ... P_N
    for (int i = 1; i <= N; i++) {
        printf("%d%c", p[i], i == N ? '\n' : ' ');
    }

    return 0;
}
