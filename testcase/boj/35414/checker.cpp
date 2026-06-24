#include "testlib.h"

#include <vector>

using namespace std;

struct Edge {
    int u;
    int v;
};

int n, m;
vector<Edge> edges;
vector<vector<int>> incident;

struct Claim {
    int operations;
};

Claim readClaim(InStream& stream) {
    int k = stream.readInt(0, n, "K");

    vector<char> controlled(m, 0);
    vector<int> remaining(n + 1, 0);
    for (int id = 0; id < m; ++id) {
        ++remaining[edges[id].u];
        ++remaining[edges[id].v];
    }

    for (int i = 0; i < k; ++i) {
        int building = stream.readInt(1, n, format("operation[%d]", i + 1).c_str());
        if (remaining[building] == 0) {
            stream.quitf(_wa,
                         "operation[%d] chooses building %d with no uncontrolled incident road",
                         i + 1,
                         building);
        }

        for (int id : incident[building]) {
            if (controlled[id]) {
                continue;
            }
            controlled[id] = 1;
            --remaining[edges[id].u];
            --remaining[edges[id].v];
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d operations", k);
    }
    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    edges.resize(m);
    incident.assign(n + 1, {});
    for (int id = 0; id < m; ++id) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges[id] = {u, v};
        incident[u].push_back(id);
        incident[v].push_back(id);
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.operations < jury.operations) {
        quitf(_wa,
              "too few operations: participant=%d jury=%d",
              participant.operations,
              jury.operations);
    }
    if (participant.operations > jury.operations) {
        quitf(_fail,
              "participant found more valid operations: participant=%d jury=%d",
              participant.operations,
              jury.operations);
    }

    quitf(_ok, "valid sequence with %d operations", participant.operations);
}
