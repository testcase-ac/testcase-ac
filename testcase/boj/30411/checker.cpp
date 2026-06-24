#include "testlib.h"

#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, k;

struct Answer {
    bool possible;
};

Answer readAnswer(InStream& stream, TResult invalidVerdict) {
    string verdict = stream.readToken("[A-Z]+", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(invalidVerdict, "extra output after NO");
        }
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(invalidVerdict, "verdict must be YES or NO, found %s", verdict.c_str());
    }

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> used;
    for (int i = 0; i < k; ++i) {
        int u = stream.readInt(1, n, format("u[%d]", i + 1).c_str());
        int v = stream.readInt(1, n, format("v[%d]", i + 1).c_str());
        if (u == v) {
            stream.quitf(invalidVerdict, "edge %d is a self-loop at vertex %d", i + 1, u);
        }
        pair<int, int> edge = minmax(u, v);
        if (!used.insert(edge).second) {
            stream.quitf(invalidVerdict, "edge %d duplicates (%d, %d)", i + 1, edge.first, edge.second);
        }
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after %d edges", k);
    }

    vector<int> color(n + 1, -1);
    queue<int> q;
    for (int start = 1; start <= n; ++start) {
        if (color[start] != -1) {
            continue;
        }
        color[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    stream.quitf(invalidVerdict, "edge (%d, %d) creates an odd cycle", u, v);
                }
            }
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (jury.possible == participant.possible) {
        quitf(_ok, "verdict %s", participant.possible ? "YES" : "NO");
    }
    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provided a valid YES certificate while jury says NO");
    }
    quitf(_wa, "jury says YES but participant says NO");
}
