#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> parent;

// DSU functions
int findRoot(int x) {
    return parent[x] == x ? x : parent[x] = findRoot(parent[x]);
}
void unite(int a, int b) {
    a = findRoot(a);
    b = findRoot(b);
    if (a != b) parent[b] = a;
}

int compCount;

// Reads an answer (either jury's or contestant's) and checks its format and consistency.
// Returns the vector of representatives.
vector<int> readAns(InStream &stream) {
    // Read number of committees K
    int K = stream.readInt(1, N, "K");
    // Must match the actual number of components
    if (K != compCount) {
        stream.quitf(_wa, "wrong number of committees: expected %d, found %d", compCount, K);
    }
    vector<int> reps;
    reps.reserve(K);
    vector<bool> usedRoot(N+1, false);
    int prevRep = 0;
    for (int i = 0; i < K; i++) {
        int r = stream.readInt(1, N, format("representative[%d]", i+1).c_str());
        // Check strictly increasing order
        if (i > 0 && r <= prevRep) {
            stream.quitf(_wa, "representatives are not in strictly increasing order");
        }
        prevRep = r;
        // Check that this component hasn't been represented already
        int root = findRoot(r);
        if (usedRoot[root]) {
            stream.quitf(_wa, "more than one representative from the same committee");
        }
        usedRoot[root] = true;
        reps.push_back(r);
    }
    // All components are represented because K == compCount and we have K distinct roots
    return reps;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input graph
    N = inf.readInt();
    M = inf.readInt();
    parent.resize(N+1);
    for (int i = 1; i <= N; i++) parent[i] = i;
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N);
        int v = inf.readInt(1, N);
        unite(u, v);
    }
    // Compress DSU and count components
    for (int i = 1; i <= N; i++) findRoot(i);
    set<int> roots;
    for (int i = 1; i <= N; i++) roots.insert(parent[i]);
    compCount = (int)roots.size();

    // Read jury and participant answers
    vector<int> juryReps = readAns(ans);
    vector<int> partReps = readAns(ouf);

    // Compare
    if (juryReps != partReps) {
        // build string representations
        auto vecToStr = [](const vector<int> &v) {
            string s;
            for (int x : v) {
                if (!s.empty()) s += ' ';
                s += to_string(x);
            }
            return s;
        };
        quitf(_wa,
              "wrong representatives: expected \"%s\", found \"%s\"",
              vecToStr(juryReps).c_str(),
              vecToStr(partReps).c_str());
    }

    quitf(_ok, "committees = %d", compCount);
    return 0;
}
