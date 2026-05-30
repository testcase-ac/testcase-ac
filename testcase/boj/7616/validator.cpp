#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int case_count = 0;
    while (true) {
        int k = inf.readInt(0, 100, "K");
        inf.readSpace();
        int n = inf.readInt(0, 5000, "N");
        inf.readEoln();

        if (k == 0 && n == 0) {
            break;
        }

        ++case_count;
        ensuref(k >= 1, "case %d: K must be positive, got %d", case_count, k);
        ensuref(n >= 2, "case %d: N must be at least 2, got %d", case_count, n);

        vector<set<int>> adj(n + 1);
        for (int u = 1; u <= n; ++u) {
            string line = inf.readLine();
            ensuref(!line.empty(), "case %d: empty adjacency list on line %d",
                    case_count, u);
            ensuref(line.front() != ' ' && line.back() != ' ',
                    "case %d: adjacency list on line %d has leading or trailing space",
                    case_count, u);
            for (size_t i = 0; i < line.size(); ++i) {
                char c = line[i];
                ensuref(('0' <= c && c <= '9') || c == ' ',
                        "case %d: invalid character on adjacency line %d",
                        case_count, u);
                ensuref(i == 0 || c != ' ' || line[i - 1] != ' ',
                        "case %d: repeated spaces on adjacency line %d",
                        case_count, u);
            }

            stringstream ss(line);
            string token;
            while (ss >> token) {
                ensuref(token.size() == 1 || token[0] != '0',
                        "case %d: leading zero in neighbor token '%s' on line %d",
                        case_count, token.c_str(), u);

                int v = stoi(token);
                ensuref(1 <= v && v <= n,
                        "case %d: neighbor %d on line %d is outside 1..%d",
                        case_count, v, u, n);

                // CHECK: The statement describes adjacent intersections, so a self-loop
                // is not a meaningful floor-plan adjacency.
                ensuref(v != u, "case %d: intersection %d lists itself", case_count, u);

                // CHECK: Adjacency is a relation; repeated indices do not describe
                // additional intersections.
                ensuref(adj[u].insert(v).second,
                        "case %d: duplicate neighbor %d on line %d",
                        case_count, v, u);
            }

            ensuref(!adj[u].empty(),
                    "case %d: intersection %d has no adjacent intersections",
                    case_count, u);
        }

        for (int u = 1; u <= n; ++u) {
            for (int v : adj[u]) {
                ensuref(adj[v].count(u) == 1,
                        "case %d: edge %d-%d is not listed in both directions",
                        case_count, u, v);
            }
        }
    }

    inf.readEof();
}
