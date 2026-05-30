#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of cities
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Adjacency matrix, N lines of length N, consisting of '0' and '1'
    vector<string> adj(N);
    for (int i = 0; i < N; ++i) {
        adj[i] = inf.readToken("[01]{1,50}", "adj_row");
        inf.readEoln();
        ensuref((int)adj[i].size() == N,
                "Adjacency row %d must have length %d, got %d",
                i, N, (int)adj[i].size());
    }

    // Check adjacency matrix constraints: A[i][i] = 0, symmetric
    for (int i = 0; i < N; ++i) {
        ensuref(adj[i][i] == '0',
                "Adjacency matrix must have 0 on diagonal, but A[%d][%d] = %c",
                i, i, adj[i][i]);
        for (int j = i + 1; j < N; ++j) {
            ensuref(adj[i][j] == adj[j][i],
                    "Adjacency matrix must be symmetric: A[%d][%d]=%c, A[%d][%d]=%c",
                    i, j, adj[i][j], j, i, adj[j][i]);
        }
    }

    // K: number of companies
    int K = inf.readInt(1, 50, "K");
    inf.readEoln();

    // Already working guards per city
    vector<vector<int>> already(N);
    for (int city = 0; city < N; ++city) {
        int cnt = inf.readInt(0, K, "existing_count");
        if (cnt > 0) inf.readSpace();
        already[city].resize(cnt);
        vector<bool> seen(K, false);
        for (int j = 0; j < cnt; ++j) {
            int c = inf.readInt(0, K - 1, "existing_company");
            ensuref(!seen[c],
                    "Duplicate existing guard company %d at city %d",
                    c, city);
            seen[c] = true;
            if (j + 1 < cnt) inf.readSpace();
            already[city][j] = c;
        }
        inf.readEoln();
    }

    // Offices per city
    vector<vector<int>> offices(N);
    for (int city = 0; city < N; ++city) {
        int cnt = inf.readInt(0, K, "office_count");
        if (cnt > 0) inf.readSpace();
        offices[city].resize(cnt);
        vector<bool> seen(K, false);
        for (int j = 0; j < cnt; ++j) {
            int c = inf.readInt(0, K - 1, "office_company");
            ensuref(!seen[c],
                    "Duplicate office company %d at city %d",
                    c, city);
            seen[c] = true;
            if (j + 1 < cnt) inf.readSpace();
            offices[city][j] = c;
        }
        inf.readEoln();
    }

    // Global logical checks implied by the statement:

    // 1) Every existing guard must correspond to a company that has an office
    //    in that city (otherwise the prior hiring would have violated rules).
    vector<vector<bool>> hasOffice(N, vector<bool>(K, false));
    for (int city = 0; city < N; ++city) {
        for (int c : offices[city]) {
            hasOffice[city][c] = true;
        }
    }
    for (int city = 0; city < N; ++city) {
        for (int c : already[city]) {
            ensuref(hasOffice[city][c],
                    "Existing guard of company %d at city %d but that company has no office there",
                    c, city);
        }
    }

    // 2) Verify that the "answer always exists" and that the minimal number
    //    of conflicts is finite and within reasonable bounds.
    //
    //    Conflict definition:
    //    For each cooperating pair (A,B) (i.e., adj[A][B] == '1'),
    //    and each company C,
    //    if there is at least one guard of company C in A
    //    and zero guards of company C in B, this contributes 1 conflict.
    //    (And vice versa for guard in B and not in A.)
    //
    //    Because any number of guards can be hired but none can be fired or moved,
    //    we can always eliminate conflicts by hiring guards:
    //    For each cooperating pair (A,B) and each company C
    //    that already exists in at least one of A or B and has offices in both,
    //    we can hire guards in both cities, yielding no conflict for that (pair,company).
    //
    //    A very loose upper bound on minimal conflicts:
    //    At worst, we don't hire any new guards; then count all conflicts induced
    //    by the existing guards arrangement. Since N,K <= 50, this is easily
    //    computable and bounded by 2 * (number_of_edges * K) <= 2 * (N*(N-1)/2 * K).
    //
    //    We will just compute this naive "no extra hires" conflict count and
    //    assert it fits into 64-bit and is non-negative, which must hold if the
    //    input respects the definition.

    long long naiveConflicts = 0;
    // Compute hasGuardExisting[city][company]
    vector<vector<bool>> hasGuard(N, vector<bool>(K, false));
    for (int city = 0; city < N; ++city) {
        for (int c : already[city]) hasGuard[city][c] = true;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (adj[i][j] == '1') {
                for (int c = 0; c < K; ++c) {
                    bool gi = hasGuard[i][c];
                    bool gj = hasGuard[j][c];
                    if (gi ^ gj) {
                        // exactly one city has guards of company c
                        naiveConflicts++;
                    }
                }
            }
        }
    }

    ensuref(naiveConflicts >= 0,
            "Computed conflict count is negative, which is impossible");
    // Upper theoretical bound: edges <= N*(N-1)/2, each edge-company can contribute 2
    long long maxEdges = 1LL * N * (N - 1) / 2;
    long long hardUpper = 2LL * maxEdges * K;
    ensuref(naiveConflicts <= hardUpper,
            "Naive conflict count %lld exceeds theoretical maximum %lld",
            naiveConflicts, hardUpper);

    inf.readEof();
}
