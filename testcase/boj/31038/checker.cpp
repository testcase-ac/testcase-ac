#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    int k;
    vector<int> p;
};

int n;
vector<pair<int, int>> edges;

struct MergeSimulator {
    vector<int> parent;
    vector<set<int>> adj;
    int components;

    explicit MergeSimulator(int vertexCount) : parent(vertexCount + 1), adj(vertexCount + 1), components(vertexCount) {
        for (int i = 1; i <= vertexCount; ++i) {
            parent[i] = i;
        }
        for (auto [u, v] : edges) {
            adj[u].insert(v);
            adj[v].insert(u);
        }
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    void absorb(int base, int other) {
        if (base == other) {
            return;
        }
        parent[other] = base;
        --components;

        for (int to : adj[other]) {
            int root = find(to);
            if (root != base && root != other) {
                adj[root].erase(other);
                adj[root].insert(base);
                adj[base].insert(root);
            }
        }
        adj[other].clear();
        adj[base].erase(base);
    }

    bool run(const vector<int>& sequence) {
        for (int person : sequence) {
            int center = find(person);
            vector<int> group;
            group.push_back(center);
            for (int to : adj[center]) {
                group.push_back(find(to));
            }
            sort(group.begin(), group.end());
            group.erase(unique(group.begin(), group.end()), group.end());

            int base = group[0];
            for (int root : group) {
                if (adj[root].size() > adj[base].size()) {
                    base = root;
                }
            }
            for (int root : group) {
                absorb(base, root);
            }
        }
        return components == 1;
    }
};

string readFirstToken(InStream& stream) {
    string token = stream.readToken();
    if (token == "IMPOSSIBLE") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after IMPOSSIBLE");
        }
        return token;
    }
    return token;
}

int parseIntToken(InStream& stream, const string& token, int minValue, int maxValue, const char* name) {
    try {
        size_t pos = 0;
        long long value = stoll(token, &pos);
        if (pos != token.size()) {
            stream.quitf(_wa, "%s is not an integer", name);
        }
        if (value < minValue || value > maxValue) {
            stream.quitf(_wa, "%s=%lld is outside [%d, %d]", name, value, minValue, maxValue);
        }
        return static_cast<int>(value);
    } catch (...) {
        stream.quitf(_wa, "%s is not an integer", name);
    }
}

Claim readClaim(InStream& stream) {
    string first = readFirstToken(stream);
    if (first == "IMPOSSIBLE") {
        return {true, -1, {}};
    }

    int k = parseIntToken(stream, first, 1, n - 1, "k");
    vector<int> p(k);
    for (int i = 0; i < k; ++i) {
        p[i] = stream.readInt(1, n, format("p[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    for (int i = 1; i + 1 < k; ++i) {
        bool leftIncreasing = p[i - 1] < p[i];
        bool rightIncreasing = p[i] < p[i + 1];
        if (leftIncreasing == rightIncreasing) {
            stream.quitf(_wa, "p[%d]=%d violates the alternating condition", i + 1, p[i]);
        }
    }

    MergeSimulator simulator(n);
    if (!simulator.run(p)) {
        stream.quitf(_wa, "sequence does not merge all people into one vertex");
    }

    return {false, k, p};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 300000, "N");
    edges.reserve(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt(1, n, format("A[%d]", i + 1).c_str());
        int v = inf.readInt(1, n, format("B[%d]", i + 1).c_str());
        edges.push_back({u, v});
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs are IMPOSSIBLE");
        }
        quitf(_fail, "participant found a valid sequence of length %d while jury says IMPOSSIBLE", participant.k);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid sequence of length %d", jury.k);
    }
    if (participant.k < jury.k) {
        quitf(_fail, "participant found a shorter valid sequence: jury=%d participant=%d", jury.k, participant.k);
    }
    if (participant.k > jury.k) {
        quitf(_wa, "sequence is not minimum: jury=%d participant=%d", jury.k, participant.k);
    }
    quitf(_ok, "valid minimum sequence of length %d", participant.k);
}
