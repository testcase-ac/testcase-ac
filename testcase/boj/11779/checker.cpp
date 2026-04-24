#include "testlib.h"
#include <vector>
#include <map>
#include <utility>
using namespace std;

int n, m;
int A, B;
map<pair<int,int>, long long> edges;

// This function reads an answer from the given stream (contestant or jury),
// checks that it is a valid path from A to B in the graph, computes its cost
// and returns that cost. On error, it quits with _wa (for contestant stream)
// or _fail (for jury stream).
long long readAns(InStream &stream) {
    // Read reported cost
    long long reported_cost = stream.readLong(0, 1000000000000LL, "cost");
    // Read number of cities in the path
    int k = stream.readInt(1, n, "number of cities");
    vector<int> path(k);
    for (int i = 0; i < k; i++) {
        path[i] = stream.readInt(1, n, format("path[%d]", i+1).c_str());
    }
    // Check endpoints
    if (path.front() != A) {
        stream.quitf(_wa, "path doesn't start at A: expected %d, found %d", A, path.front());
    }
    if (path.back() != B) {
        stream.quitf(_wa, "path doesn't end at B: expected %d, found %d", B, path.back());
    }
    // Check edges and accumulate actual cost
    long long actual_cost = 0;
    for (int i = 0; i+1 < k; i++) {
        int u = path[i], v = path[i+1];
        auto it = edges.find(make_pair(u, v));
        if (it == edges.end()) {
            stream.quitf(_wa, "no edge from %d to %d", u, v);
        }
        actual_cost += it->second;
    }
    // Check reported cost matches actual cost
    if (actual_cost != reported_cost) {
        stream.quitf(_wa, "reported cost = %lld but actual cost = %lld", reported_cost, actual_cost);
    }
    return actual_cost;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input graph
    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        int w = inf.readInt();
        auto key = make_pair(u, v);
        auto it = edges.find(key);
        if (it == edges.end() || w < it->second) {
            edges[key] = w;
        }
    }
    A = inf.readInt();
    B = inf.readInt();
    // Read jury answer
    long long jcost = readAns(ans);
    // Read participant answer
    long long pcost = readAns(ouf);
    // Compare
    if (pcost > jcost) {
        quitf(_wa, "jury has a better answer: jans = %lld, pans = %lld", jcost, pcost);
    } else if (pcost < jcost) {
        quitf(_fail, "participant has a strictly better answer: jans = %lld, pans = %lld", jcost, pcost);
    } else {
        quitf(_ok, "cost = %lld", pcost);
    }
    return 0;
}
