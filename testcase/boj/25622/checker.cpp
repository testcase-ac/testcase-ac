#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
long long M;
unordered_set<long long> edges;

// Helper to generate a unique key for an undirected edge (u, v)
inline long long edgeKey(int u, int v) {
    if (u > v) std::swap(u, v);
    return (long long)u * M + v;
}

// Reads an answer (jury or participant), checks its correctness, and returns
// 0 if the verdict is 'U' (impossible), or 1 if it's 'S' (possible) with a valid grouping.
// On errors in the jury's file it quits with _fail, and on errors in the contestant's
// output it quits with _wa, thanks to stream.quitf().
int readAns(InStream &stream) {
    // Read the verdict token: must be "S" or "U"
    string verdict = stream.readToken();
    if (verdict != "S" && verdict != "U") {
        stream.quitf(_wa, "expected verdict 'S' or 'U', found '%s'", verdict.c_str());
    }
    if (verdict == "U") {
        // No grouping should follow
        stream.readEof();
        return 0;
    }
    // verdict == "S": read and validate n/3 triples
    int groups = n / 3;
    vector<char> used(n+1, 0);
    for (int i = 0; i < groups; i++) {
        int a = stream.readInt(1, n,    format("group[%d].a", i+1).c_str());
        int b = stream.readInt(1, n,    format("group[%d].b", i+1).c_str());
        int c = stream.readInt(1, n,    format("group[%d].c", i+1).c_str());
        // Check for duplicate usage
        if (used[a]) stream.quitf(_wa, "vertex %d is used more than once", a);
        if (used[b]) stream.quitf(_wa, "vertex %d is used more than once", b);
        if (used[c]) stream.quitf(_wa, "vertex %d is used more than once", c);
        used[a] = used[b] = used[c] = 1;
        // Check connectivity: in a tree, 3 vertices are connected iff induced edges = 2
        int cnt = 0;
        if (edges.count(edgeKey(a,b))) cnt++;
        if (edges.count(edgeKey(a,c))) cnt++;
        if (edges.count(edgeKey(b,c))) cnt++;
        if (cnt != 2) {
            stream.quitf(_wa, "group %d = {%d, %d, %d} does not form a connected subgraph", 
                         i+1, a, b, c);
        }
    }
    // No extra output
    stream.readEof();
    return 1;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the input tree
    n = inf.readInt();
    M = (long long)n + 1;
    for (int i = 0; i < n-1; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.insert(edgeKey(u,v));
    }

    // Read jury answer and contestant answer
    int jans = readAns(ans);
    int pans = readAns(ouf);

    // Compare verdicts
    if (jans == 0 && pans == 0) {
        quitf(_ok, "both say impossible");
    }
    if (jans == 0 && pans == 1) {
        quitf(_wa, "jury says impossible but contestant found a grouping");
    }
    if (jans == 1 && pans == 0) {
        quitf(_wa, "jury says possible but contestant says impossible");
    }
    // jans == 1 && pans == 1
    quitf(_ok, "valid grouping of size %d", n/3);
    return 0;
}
