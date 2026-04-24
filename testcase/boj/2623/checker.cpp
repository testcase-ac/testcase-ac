#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

int N, M;
vector<pair<int,int>> edges;

// This function reads an answer from 'stream', checks its validity,
// and returns the ordering as a vector<int>. If the answer is "0",
// it returns a vector of size 1 with element 0. On invalid output
// from participant it quits with _wa, from jury with _fail.
vector<int> readAns(InStream &stream) {
    vector<int> ord;
    // Read the first integer
    int x = stream.readInt(0, N, "first element");
    ord.push_back(x);
    if (x == 0) {
        // must be the only thing
        if (!stream.seekEof())
            stream.quitf(_wa, "extra output after 0");
        return ord;
    }
    // Read remaining N-1 elements
    for (int i = 1; i < N; i++) {
        int y = stream.readInt(1, N, format("element %d", i+1).c_str());
        ord.push_back(y);
    }
    if (!stream.seekEof())
        stream.quitf(_wa, "extra output after reading %d elements", N);
    // Check it's a valid permutation
    vector<bool> used(N+1, false);
    for (int i = 0; i < N; i++) {
        int v = ord[i];
        if (v < 1 || v > N)
            stream.quitf(_wa, "element %d is out of range: %d", i+1, v);
        if (used[v])
            stream.quitf(_wa, "element %d is repeated: %d", i+1, v);
        used[v] = true;
    }
    // Build position map
    vector<int> pos(N+1);
    for (int i = 0; i < N; i++)
        pos[ord[i]] = i;
    // Check constraints: for each edge u->v, u must come before v
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        if (pos[u] >= pos[v])
            stream.quitf(_wa,
                "ordering violates constraint: %d should come before %d", u, v);
    }
    return ord;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt();
    M = inf.readInt();
    for (int i = 0; i < M; i++) {
        int k = inf.readInt();
        vector<int> a(k);
        for (int j = 0; j < k; j++)
            a[j] = inf.readInt();
        for (int j = 0; j+1 < k; j++)
            edges.emplace_back(a[j], a[j+1]);
    }
    // Read jury and participant answers
    vector<int> jans = readAns(ans);
    vector<int> pans = readAns(ouf);

    // If jury says impossible
    if (jans.size() == 1 && jans[0] == 0) {
        // participant must also say 0 (otherwise we'd have WA earlier)
        quitf(_ok, "both say impossible");
    } else {
        // jury gives a valid ordering
        if (pans.size() == 1 && pans[0] == 0) {
            quitf(_wa, "participant says impossible but solution exists");
        } else {
            quitf(_ok, "correct ordering");
        }
    }
    return 0;
}
