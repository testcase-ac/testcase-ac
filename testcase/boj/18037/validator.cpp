#include "testlib.h"
#include <vector>

using namespace std;

enum class VisitState {
    Unvisited,
    Visiting,
    Done,
};

void dfsAcyclic(int v, const vector<vector<int>>& graph, vector<VisitState>& state) {
    state[v] = VisitState::Visiting;

    for (int to : graph[v]) {
        ensuref(state[to] != VisitState::Visiting,
                "mailing list dependency cycle uses edge %d -> %d", v, to);
        if (state[to] == VisitState::Unvisited) {
            dfsAcyclic(to, graph, state);
        }
    }

    state[v] = VisitState::Done;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int l = inf.readInt(1, min(n - 1, 1000), "L");
    inf.readEoln();

    vector<vector<int>> listEdges(l + 1);
    vector<bool> clientSeen(n + 1, false);

    for (int i = 1; i <= l; ++i) {
        int k = inf.readInt(1, n - 1, "K");
        vector<bool> seen(n + 1, false);

        for (int j = 1; j <= k; ++j) {
            inf.readSpace();
            int m = inf.readInt(1, n, "M");
            ensuref(!seen[m], "duplicate address %d in mailing list %d", m, i);
            seen[m] = true;

            if (m <= l) {
                listEdges[i].push_back(m);
            } else {
                clientSeen[m] = true;
            }
        }
        inf.readEoln();
    }

    for (int client = l + 1; client <= n; ++client) {
        ensuref(clientSeen[client], "client address %d does not appear in any mailing list", client);
    }

    // CHECK: cyclic mailing-list inclusion would make the message count undefined.
    vector<VisitState> state(l + 1, VisitState::Unvisited);
    for (int i = 1; i <= l; ++i) {
        if (state[i] == VisitState::Unvisited) {
            dfsAcyclic(i, listEdges, state);
        }
    }

    inf.readEof();
}
