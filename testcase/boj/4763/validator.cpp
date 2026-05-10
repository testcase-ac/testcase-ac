#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n = 0): n(n), p(n), r(n,0) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x){
        if (p[x]==x) return x;
        return p[x]=find(p[x]);
    }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if (a==b) return false;
        if (r[a]<r[b]) swap(a,b);
        p[b]=a;
        if (r[a]==r[b]) r[a]++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: length of cable on the spool as a real number.
    // Use readToken + parse as double, enforce canonical form (no leading +, "0" or "0.xxx" allowed).
    string cableStr = inf.readToken("[^ ]+", "cable_length");
    inf.readEoln();

    auto isCanonicalReal = [](const string &s) -> bool {
        // Allowed: optional '-', digits with no leading zeros unless "0",
        // optional fractional part with digits (allows "0.0", "10.25", "-3.5").
        // Disallow "+", leading zeros like "01", ".", "1.", "-.5", empty fraction "1.".
        if (s.empty()) return false;
        int pos = 0;
        bool neg = false;
        if (s[pos] == '-') {
            neg = true;
            pos++;
            if (pos == (int)s.size()) return false; // just "-"
        } else if (s[pos] == '+') {
            return false;
        }
        // now s[pos..] is number with optional fractional part
        int dotPos = -1;
        for (int i = pos; i < (int)s.size(); ++i) {
            if (s[i] == '.') {
                if (dotPos != -1) return false; // multiple dots
                dotPos = i;
            } else if (!(s[i] >= '0' && s[i] <= '9')) {
                return false;
            }
        }
        if (dotPos == -1) {
            // integer
            string intPart = s.substr(pos);
            if (intPart.empty()) return false;
            if (intPart.size() > 1 && intPart[0] == '0') return false;
        } else {
            string intPart = s.substr(pos, dotPos - pos);
            string fracPart = s.substr(dotPos + 1);
            if (intPart.empty()) return false;       // no ".x"
            if (fracPart.empty()) return false;      // no "x."
            if (intPart.size() > 1 && intPart[0] == '0') return false;
        }
        return true;
    };

    ensuref(isCanonicalReal(cableStr),
            "cable_length is not in canonical real format: '%s'",
            cableStr.c_str());
    double cableLen;
    {
        std::stringstream ss(cableStr);
        ss >> cableLen;
        ensuref(!ss.fail() && ss.eof(), "Failed to parse cable_length as double");
    }
    ensuref(cableLen >= 0.0,
            "cable_length must be non-negative");

    // Second line: N, number of houses (integer, no constraints given; assume 1..100000)
    long long N = inf.readLong(1LL, 100000LL, "N");
    inf.readEoln();

    // Next N lines: house owner names, token of up to 20 chars [a-zA-Z0-9], no whitespace.
    vector<string> names;
    names.reserve((size_t)N);
    unordered_map<string,int> id;
    id.reserve((size_t)N * 2);

    for (int i = 0; i < N; ++i) {
        string nm = inf.readToken("[0-9A-Za-z]{1,20}", "name");
        inf.readEoln();
        ensuref(!id.count(nm), "Duplicate house name at index %d: '%s'", i, nm.c_str());
        id[nm] = i;
        names.push_back(nm);
    }

    // Next line: M, number of paths between houses.
    long long M = inf.readLong(0LL, 100000LL, "M");
    inf.readEoln();

    struct Edge {
        int u, v;
        double w;
    };
    vector<Edge> edges;
    edges.reserve((size_t)M);
    set<pair<int,int>> seen;

    for (int i = 0; i < M; ++i) {
        string a = inf.readToken("[0-9A-Za-z]{1,20}", "houseA");
        inf.readSpace();
        string b = inf.readToken("[0-9A-Za-z]{1,20}", "houseB");
        inf.readSpace();
        string distStr = inf.readToken("[^ ]+", "distance");
        inf.readEoln();

        auto itA = id.find(a);
        auto itB = id.find(b);
        ensuref(itA != id.end(), "Edge %d: unknown house name A '%s'", i, a.c_str());
        ensuref(itB != id.end(), "Edge %d: unknown house name B '%s'", i, b.c_str());
        int u = itA->second;
        int v = itB->second;
        ensuref(u != v, "Edge %d: self-loop for house '%s'", i, a.c_str());

        ensuref(isCanonicalReal(distStr),
                "Edge %d: distance is not in canonical real format: '%s'",
                i, distStr.c_str());
        double w;
        {
            std::stringstream ss(distStr);
            ss >> w;
            ensuref(!ss.fail() && ss.eof(),
                    "Edge %d: failed to parse distance as double", i);
        }
        ensuref(w > 0.0, "Edge %d: distance must be positive", i);

        int x = u, y = v;
        if (x > y) swap(x, y);
        ensuref(!seen.count({x,y}),
                "Multiple edges detected between '%s' and '%s'", a.c_str(), b.c_str());
        seen.insert({x,y});

        edges.push_back({u,v,w});
    }

    // Global property: all houses can be connected with given paths (graph must be connected).
    DSU dsu((int)N);
    for (auto &e : edges) dsu.unite(e.u, e.v);
    int root = dsu.find(0);
    for (int i = 1; i < N; ++i) {
        ensuref(dsu.find(i) == root,
                "Graph is not connected: node index %d ('%s') not in main component",
                i, names[i].c_str());
    }

    // Global property from statement: "You want to calculate the shortest length ...
    // you must have to connect all of the houses together." This is the MST weight.
    // No explicit bound on answer, but we should ensure MST always exists (already ensured
    // by connectivity) and we can compute it (no overflow in double).
    // We also check that printed value X to nearest tenth is well-defined; that's trivial,
    // but we compute MST to be able to cross-check if problem's assumption "answer always exists"
    // holds.
    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b){ return a.w < b.w; });
    DSU mstDsu((int)N);
    double mstSum = 0.0;
    int used = 0;
    for (auto &e : edges) {
        if (mstDsu.unite(e.u, e.v)) {
            mstSum += e.w;
            used++;
            if (used == N - 1) break;
        }
    }
    ensuref(used == N - 1,
            "MST does not span all nodes (used edges = %d, expected %lld). Graph connectivity check inconsistent.",
            used, N - 1);

    // Optionally, we may verify that the cable length bound is not negative w.r.t MST if
    // problem stated something like "answer at most X". Here no max bound is given,
    // so we only ensured existence.

    inf.readEof();
}
