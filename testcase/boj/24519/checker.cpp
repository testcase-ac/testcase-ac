#include "testlib.h"

#include <map>
#include <utility>
#include <vector>

using namespace std;

int n, m;
map<pair<int, int>, int> cost;

struct Answer {
    bool impossible;
    int value;
};

Answer readAnswer(InStream& stream) {
    int claimed = stream.readInt(-1, 5000000, "answer");
    stream.readEoln();

    if (claimed == -1) {
        stream.readEof();
        return {true, -1};
    }

    vector<int> path(n);
    vector<int> used(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        path[i] = stream.readInt(1, n, format("path[%d]", i + 1).c_str());
        if (used[path[i]]) {
            stream.quitf(_wa, "vertex %d appears more than once", path[i]);
        }
        used[path[i]] = 1;
    }
    stream.readEoln();
    stream.readEof();

    int actual = 0;
    for (int i = 0; i < n; ++i) {
        int from = path[i];
        int to = path[(i + 1) % n];
        auto it = cost.find({from, to});
        if (it == cost.end()) {
            stream.quitf(_wa, "edge %d -> %d is not present in the graph", from, to);
        }
        actual = max(actual, it->second);
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed answer is %d, but the supplied cycle has bottleneck %d",
                     claimed, actual);
    }

    return {false, actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        int c = inf.readInt();
        cost[{u, v}] = c;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim no Hamiltonian cycle");
        }
        quitf(_fail, "participant supplied a valid cycle with bottleneck %d while jury says -1",
              participant.value);
    }

    if (participant.impossible) {
        quitf(_wa, "participant says -1, but jury has a cycle with bottleneck %d", jury.value);
    }

    if (participant.value < jury.value) {
        quitf(_fail, "participant found a better cycle: jury=%d participant=%d",
              jury.value, participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_wa, "participant cycle is worse than jury: jury=%d participant=%d",
              jury.value, participant.value);
    }

    quitf(_ok, "answer=%d", participant.value);
}
