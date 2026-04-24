#include "testlib.h"
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;

int n;
vector<long long> weight;
vector<vector<int>> g;

// Reads an answer (jury or contestant) from 'stream'.
// Checks that it describes a valid independent set, its sum of weights matches the declared sum,
// and returns the declared sum.
// On invalid, quits with _wa if stream==ouf, or _fail if stream==ans.
long long readAns(InStream &stream) {
    // Read declared sum
    long long declared = stream.readLong();
    stream.readEoln();

    // Read second line as whole and parse integers
    string line = stream.readLine();
    vector<int> vs;
    if (!line.empty()) {
        istringstream iss(line);
        int x;
        while (iss >> x) {
            vs.push_back(x);
        }
    }

    // Check that vs is strictly increasing and in [1..n]
    for (size_t i = 0; i < vs.size(); i++) {
        int v = vs[i];
        if (v < 1 || v > n) {
            stream.quitf(_wa, "vertex %d is out of range [1..%d]", v, n);
        }
        if (i > 0 && vs[i] <= vs[i-1]) {
            stream.quitf(_wa, "vertex list must be strictly increasing; problem at position %d", int(i+1));
        }
    }

    // Check independence and compute actual sum
    vector<char> used(n+1, 0);
    long long actual = 0;
    for (int v : vs) {
        // check neighbors
        for (int u : g[v]) {
            if (used[u]) {
                stream.quitf(_wa, "vertices %d and %d are adjacent", u, v);
            }
        }
        used[v] = 1;
        actual += weight[v];
    }

    // Check declared vs actual
    if (declared != actual) {
        stream.quitf(_wa, "declared sum = %lld, but actual sum = %lld", declared, actual);
    }
    return declared;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input graph
    n = inf.readInt();
    weight.assign(n+1, 0);
    for (int i = 1; i <= n; i++) {
        weight[i] = inf.readInt();
    }
    g.assign(n+1, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // Read jury and participant answers
    long long jans = readAns(ans);
    long long pans = readAns(ouf);

    if (pans < jans) {
        quitf(_wa, "jury has better answer: jury = %lld, participant = %lld", jans, pans);
    } else if (pans > jans) {
        quitf(_fail, "participant has strictly better answer than jury: jury = %lld, participant = %lld", jans, pans);
    } else {
        quitf(_ok, "max weight = %lld", pans);
    }
    return 0;
}
