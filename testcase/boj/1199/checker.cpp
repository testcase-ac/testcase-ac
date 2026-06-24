#include "testlib.h"

#include <vector>
using namespace std;

int n;
int edgeCount;
vector<vector<int>> graph;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<int> path;
    path.push_back(first);
    while (!stream.seekEof()) {
        path.push_back(stream.readInt(1, n, format("path[%d]", int(path.size()) + 1).c_str()));
    }

    if ((int)path.size() != edgeCount + 1) {
        stream.quitf(_wa,
                     "Euler circuit should contain %d vertices, found %d",
                     edgeCount + 1,
                     int(path.size()));
    }
    if (path.front() != path.back()) {
        stream.quitf(_wa,
                     "Euler circuit starts at %d but ends at %d",
                     path.front(),
                     path.back());
    }

    vector<vector<int>> remaining = graph;
    for (int i = 0; i + 1 < (int)path.size(); ++i) {
        int u = path[i] - 1;
        int v = path[i + 1] - 1;
        if (remaining[u][v] == 0) {
            stream.quitf(_wa,
                         "edge %d -> %d at step %d is not available",
                         path[i],
                         path[i + 1],
                         i + 1);
        }
        --remaining[u][v];
        --remaining[v][u];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (remaining[i][j] != 0) {
                stream.quitf(_wa,
                             "edge multiplicity remains between %d and %d",
                             i + 1,
                             j + 1);
            }
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    graph.assign(n, vector<int>(n));
    edgeCount = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            graph[i][j] = inf.readInt();
            if (i < j) {
                edgeCount += graph[i][j];
            }
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid Euler circuit while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has an Euler circuit");
    }

    quitf(_ok, "valid Euler circuit with %d edges", edgeCount);
}
