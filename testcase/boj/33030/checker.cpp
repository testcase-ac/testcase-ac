#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Operation {
    bool isSet;
    bool expected;
};

struct Claim {
    bool impossible;
};

int n, m;
vector<Operation> operations;
vector<pair<int, int>> edges;

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, n, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first == 0) {
        stream.quitf(_wa, "answer[1] is 0, expected -1 or an operation index");
    }

    vector<int> order(n);
    vector<int> position(n + 1, -1);
    vector<bool> used(n + 1, false);

    order[0] = first;
    used[first] = true;
    position[first] = 0;

    for (int i = 1; i < n; ++i) {
        order[i] = stream.readInt(1, n, format("answer[%d]", i + 1).c_str());
        if (used[order[i]]) {
            stream.quitf(_wa, "operation %d appears more than once", order[i]);
        }
        used[order[i]] = true;
        position[order[i]] = i;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operation order");
    }

    for (auto [from, to] : edges) {
        if (position[from] > position[to]) {
            stream.quitf(_wa,
                         "edge %d -> %d is violated: positions are %d and %d",
                         from,
                         to,
                         position[from] + 1,
                         position[to] + 1);
        }
    }

    bool reg = false;
    for (int i = 0; i < n; ++i) {
        int opIndex = order[i];
        const Operation& op = operations[opIndex];
        bool actual;
        if (op.isSet) {
            actual = !reg;
            if (!reg) {
                reg = true;
            }
        } else {
            actual = reg;
            if (reg) {
                reg = false;
            }
        }
        if (actual != op.expected) {
            stream.quitf(_wa,
                         "operation %d at position %d returns %s, expected %s",
                         opIndex,
                         i + 1,
                         actual ? "true" : "false",
                         op.expected ? "true" : "false");
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "n");
    operations.assign(n + 1, Operation{false, false});

    for (int i = 1; i <= n; ++i) {
        string type = inf.readToken("set|unset", format("type[%d]", i).c_str());
        string result = inf.readToken("true|false", format("result[%d]", i).c_str());
        operations[i] = {type == "set", result == "true"};
    }

    m = inf.readInt(0, 100000, "m");
    edges.reserve(m);
    for (int i = 0; i < m; ++i) {
        int from = inf.readInt(1, n, format("edge[%d].from", i + 1).c_str());
        int to = inf.readInt(1, n, format("edge[%d].to", i + 1).c_str());
        edges.push_back({from, to});
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant produced a valid order while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury provides a valid order");
    }

    quitf(_ok, "valid operation order");
}
