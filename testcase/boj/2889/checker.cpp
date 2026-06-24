#include "testlib.h"
#include <vector>
using namespace std;

int N, E;
vector<pair<int, int>> edges;
vector<vector<int>> incidentEdges;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream, TResult invalidResult) {
    int first = stream.readInt(0, 2, "answer[1]");

    if (first == 0) {
        if (!stream.seekEof()) {
            stream.quitf(invalidResult, "extra output after impossible marker");
        }
        return {true};
    }

    vector<int> color(E);
    color[0] = first;
    for (int i = 1; i < E; ++i) {
        color[i] = stream.readInt(1, 2, format("answer[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after assignment");
    }

    for (int city = 1; city <= N; ++city) {
        if (incidentEdges[city].size() < 2) {
            continue;
        }

        bool hasFirst = false;
        bool hasSecond = false;
        for (int edgeIndex : incidentEdges[city]) {
            hasFirst = hasFirst || color[edgeIndex] == 1;
            hasSecond = hasSecond || color[edgeIndex] == 2;
        }

        if (!hasFirst || !hasSecond) {
            stream.quitf(invalidResult,
                         "city %d has degree %d but incident colors are not both present",
                         city,
                         (int)incidentEdges[city].size());
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    N = inf.readInt();
    E = inf.readInt();
    edges.resize(E);
    incidentEdges.assign(N + 1, {});

    for (int i = 0; i < E; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges[i] = {u, v};
        incidentEdges[u].push_back(i);
        incidentEdges[v].push_back(i);
    }

    Claim jury = readClaim(ans, _fail);
    Claim participant = readClaim(ouf, _wa);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs report impossible");
    }
    if (jury.impossible) {
        quitf(_fail, "participant found a valid assignment while jury reports impossible");
    }
    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has a valid assignment");
    }

    quitf(_ok, "valid assignment");
}
