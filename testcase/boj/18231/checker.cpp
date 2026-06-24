#include "testlib.h"

#include <vector>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<bool> targetDestroyed;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "answer");

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true};
    }

    int bombCount = first;
    vector<bool> used(n + 1, false);
    vector<bool> destroyed(n + 1, false);

    stream.readEoln();
    for (int i = 0; i < bombCount; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        int city = stream.readInt(1, n, format("bomb[%d]", i + 1).c_str());
        if (used[city]) {
            stream.quitf(_wa, "bomb city %d is repeated", city);
        }
        used[city] = true;

        destroyed[city] = true;
        for (int next : graph[city]) {
            destroyed[next] = true;
        }
    }
    stream.readEoln();
    stream.readEof();

    for (int city = 1; city <= n; ++city) {
        if (destroyed[city] != targetDestroyed[city]) {
            stream.quitf(_wa,
                         "bomb list makes city %d %s, but target says %s",
                         city,
                         destroyed[city] ? "destroyed" : "not destroyed",
                         targetDestroyed[city] ? "destroyed" : "not destroyed");
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    graph.assign(n + 1, {});

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int k = inf.readInt();
    targetDestroyed.assign(n + 1, false);
    for (int i = 0; i < k; ++i) {
        int city = inf.readInt();
        targetDestroyed[city] = true;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant provided a valid witness while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid witness, but participant reports impossible");
    }

    quitf(_ok, "valid bomb list");
}
