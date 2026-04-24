/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

bool bipartite_graphical(const vector<int>& A, const vector<int>& B) {
    int N = A.size(), M = B.size();
    vector<int> r = A, c = B;
    sort(r.begin(), r.end(), greater<int>());
    sort(c.begin(), c.end(), greater<int>());
    int sumr = accumulate(r.begin(), r.end(), 0);
    int sumc = accumulate(c.begin(), c.end(), 0);
    if (sumr != sumc) return false;
    for (int k = 1; k <= N; k++) {
        long long L = 0, R = 0;
        for (int i = 0; i < k; i++) L += r[i];
        for (int j = 0; j < M; j++) R += min(k, c[j]);
        if (L > R) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // choose small team sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    vector<int> A, B;
    int E;
    // generate until we get a bipartite-graphical degree sequence
    while (true) {
        E = rnd.next(0, N * M);
        // build A
        A.assign(N, 0);
        vector<int> availA(N);
        iota(availA.begin(), availA.end(), 0);
        bool fail = false;
        for (int e = 0; e < E; e++) {
            if (availA.empty()) { fail = true; break; }
            int i = rnd.any(availA);
            A[i]++;
            if (A[i] == M) {
                // remove i
                availA.erase(find(availA.begin(), availA.end(), i));
            }
        }
        if (fail) continue;
        // build B
        B.assign(M, 0);
        vector<int> availB(M);
        iota(availB.begin(), availB.end(), 0);
        for (int e = 0; e < E; e++) {
            if (availB.empty()) { fail = true; break; }
            int j = rnd.any(availB);
            B[j]++;
            if (B[j] == N) {
                availB.erase(find(availB.begin(), availB.end(), j));
            }
        }
        if (fail) continue;
        // check bipartite graphical
        if (bipartite_graphical(A, B)) break;
    }
    // output
    printf("%d %d\n", N, M);
    for (int i = 0; i < N; i++)
        printf("%d%c", A[i], i+1==N?'\n':' ');
    for (int j = 0; j < M; j++)
        printf("%d%c", B[j], j+1==M?'\n':' ');
    return 0;
}
