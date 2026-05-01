#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter ranges for N and M
    vector<pair<int,int>> rangesN = {{1,1},{2,5},{6,20},{21,100}};
    vector<pair<int,int>> rangesM = {{1,1},{2,5},{6,20},{21,100}};
    auto rN = rnd.any(rangesN);
    int N = rnd.next(rN.first, rN.second);
    auto rM = rnd.any(rangesM);
    int M = rnd.next(rM.first, rM.second);
    // Generate problem scores
    vector<int> w(N);
    if (rnd.next(0,9) == 0) {
        // all weights equal
        int v = rnd.next(1,100);
        for (int i = 0; i < N; i++) w[i] = v;
    } else {
        for (int i = 0; i < N; i++) w[i] = rnd.next(1,100);
    }
    // Generate unique IDs <=100000
    int idMax = max(100, M * 10);
    vector<int> idPool(idMax);
    iota(idPool.begin(), idPool.end(), 1);
    shuffle(idPool.begin(), idPool.end());
    idPool.resize(M);
    // Generate answers matrix
    vector<string> ans(M, string(N, 'X'));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            ans[i][j] = rnd.next(0,1) == 0 ? 'O' : 'X';
        }
    }
    // Optional tie-case: force two perfect scorers
    bool tieCase = (M >= 2 && rnd.next(0,3) == 0);
    if (tieCase) {
        int i1 = rnd.next(0, M-1), i2;
        do { i2 = rnd.next(0, M-1); } while (i2 == i1);
        for (int j = 0; j < N; j++) {
            ans[i1][j] = ans[i2][j] = 'O';
        }
    }
    // Compute scores
    vector<int> score(M, 0);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            if (ans[i][j] == 'O') score[i] += w[j];
    }
    // Ensure unique max when not tieCase
    if (!tieCase) {
        int mx = *max_element(score.begin(), score.end());
        vector<int> tied;
        for (int i = 0; i < M; i++)
            if (score[i] == mx) tied.push_back(i);
        if (tied.size() > 1) {
            // keep the one with smallest ID, lower others
            int keep = tied[0];
            for (int i : tied)
                if (idPool[i] < idPool[keep]) keep = i;
            for (int i : tied) if (i != keep) {
                // flip one 'O' to 'X'
                for (int j = 0; j < N; j++) if (ans[i][j] == 'O') {
                    ans[i][j] = 'X';
                    score[i] -= w[j];
                    break;
                }
                break;
            }
        }
    }
    // Output
    println(N, M);
    println(w);
    for (int i = 0; i < M; i++) {
        printf("%d", idPool[i]);
        for (int j = 0; j < N; j++)
            printf(" %c", ans[i][j]);
        printf("\n");
    }
    return 0;
}
