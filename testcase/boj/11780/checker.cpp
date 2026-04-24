#include "testlib.h"
#include <vector>
#include <map>
#include <utility>
#include <string>
using namespace std;

int n, m;
map<pair<int,int>, int> adj;

// Structure to hold the full answer: cost matrix and paths
struct Answer {
    vector<vector<int>> cost;
    vector<vector<vector<int>>> path;
};

// Read an answer (jury or participant) from stream, validate it against the graph,
// and return the parsed Answer. On any error in 'stream', quits with _wa if stream==ouf
// or with _fail if stream==ans.
Answer readAns(InStream &stream) {
    Answer A;
    A.cost.assign(n, vector<int>(n));
    A.path.assign(n, vector<vector<int>>(n));
    // Read cost matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string label = "cost[" + to_string(i+1) + "][" + to_string(j+1) + "]";
            A.cost[i][j] = stream.readInt(0, 1000000000, label.c_str());
        }
    }
    // Read paths
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string label = "k[" + to_string(i+1) + "][" + to_string(j+1) + "]";
            int k = stream.readInt(0, n, label.c_str());
            if (k == 0) {
                // no path
                continue;
            }
            // must have at least start and end
            if (k < 2) {
                stream.quitf(_wa, "path length for (%d,%d) must be 0 or >=2, found %d", i+1, j+1, k);
            }
            vector<int> p(k);
            for (int t = 0; t < k; t++) {
                string lbl = "path[" + to_string(i+1) + "][" + to_string(j+1) + "][" + to_string(t+1) + "]";
                p[t] = stream.readInt(1, n, lbl.c_str());
            }
            // check endpoints
            if (p.front() != i+1) {
                stream.quitf(_wa, "path for (%d,%d) starts at %d not %d", i+1, j+1, p.front(), i+1);
            }
            if (p.back() != j+1) {
                stream.quitf(_wa, "path for (%d,%d) ends at %d not %d", i+1, j+1, p.back(), j+1);
            }
            // check adjacency and compute sum
            long long sum = 0;
            for (int t = 0; t+1 < k; t++) {
                int u = p[t], v = p[t+1];
                auto it = adj.find(make_pair(u, v));
                if (it == adj.end()) {
                    stream.quitf(_wa, "no bus from %d to %d on path for (%d,%d)", u, v, i+1, j+1);
                }
                sum += it->second;
            }
            // sum must equal reported cost
            if (sum != A.cost[i][j]) {
                stream.quitf(_wa, "path cost %lld for (%d,%d) does not match reported cost %d", sum, i+1, j+1, A.cost[i][j]);
            }
            A.path[i][j] = p;
        }
    }
    return A;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input graph
    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n);
        int b = inf.readInt(1, n);
        int c = inf.readInt(1, 100000);
        pair<int,int> e = make_pair(a, b);
        auto it = adj.find(e);
        if (it == adj.end() || c < it->second) {
            adj[e] = c;
        }
    }
    // Read jury and participant answers
    Answer jury = readAns(ans);
    Answer part = readAns(ouf);
    // No extra tokens in participant output
    if (!ouf.seekEof()) {
        ouf.quitf(_pe, "extra tokens after reading all answers");
    }
    // Compare cost matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (jury.cost[i][j] != part.cost[i][j]) {
                quitf(_wa, "cost[%d][%d] mismatch: expected %d, found %d",
                      i+1, j+1, jury.cost[i][j], part.cost[i][j]);
            }
        }
    }
    // All checks passed
    quitf(_ok, "correct");
    return 0;
}
