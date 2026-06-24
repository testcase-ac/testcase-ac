#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1000000007;

int n, m;
vector<vector<int>> cost;

struct Answer {
    bool impossible;
    int claimed;
    int objective;
};

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(-1, 5000000, "answer");
    if (claimed == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, -1, -1};
    }

    vector<int> order(n);
    vector<int> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        order[i] = stream.readInt(1, n, format("order[%d]", i + 1).c_str());
        if (seen[order[i]]) {
            stream.quitf(_wa, "vertex %d appears more than once", order[i]);
        }
        seen[order[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after tour");
    }

    int objective = 0;
    for (int i = 0; i < n; ++i) {
        int from = order[i];
        int to = order[(i + 1) % n];
        if (cost[from][to] == INF) {
            stream.quitf(_wa, "edge %d -> %d is not present", from, to);
        }
        objective = max(objective, cost[from][to]);
    }

    if (claimed != objective) {
        stream.quitf(_wa,
                     "claimed value %d does not match tour bottleneck %d",
                     claimed,
                     objective);
    }

    return {false, claimed, objective};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    cost.assign(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        int c = inf.readInt();
        cost[u][v] = c;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers report impossible");
        }
        quitf(_fail,
              "participant found a valid tour with bottleneck %d while jury reports impossible",
              participant.objective);
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has bottleneck %d", jury.objective);
    }

    if (participant.objective < jury.objective) {
        quitf(_fail,
              "participant found a better tour: participant=%d jury=%d",
              participant.objective,
              jury.objective);
    }
    if (participant.objective > jury.objective) {
        quitf(_wa,
              "participant tour is worse: participant=%d jury=%d",
              participant.objective,
              jury.objective);
    }

    quitf(_ok, "answer=%d", participant.objective);
}
