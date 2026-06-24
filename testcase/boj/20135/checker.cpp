#include "testlib.h"

#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    long long low;
    long long high;
};

struct Claim {
    int status;
    bool hasFlow;
};

int n, m;
vector<long long> p;
vector<Edge> edges;

Claim readClaim(InStream& stream) {
    int status = stream.readInt(-1, 1, "status");
    if (status == 0) {
        stream.quitf(_wa, "status must be 1 or -1, found 0");
    }
    stream.readEoln();

    if (status == -1) {
        stream.readEof();
        return {status, false};
    }

    vector<long long> balance(n, 0);
    for (int i = 0; i < m; ++i) {
        const Edge& edge = edges[i];
        long long flow = stream.readLong(edge.low, edge.high, format("flow[%d]", i + 1).c_str());
        stream.readEoln();

        balance[edge.from] -= flow;
        balance[edge.to] += flow;
    }
    stream.readEof();

    for (int i = 0; i < n; ++i) {
        long long outMinusIn = -balance[i];
        if (outMinusIn != p[i]) {
            stream.quitf(_wa,
                         "node %d has outgoing-incoming=%lld, expected %lld",
                         i + 1,
                         outMinusIn,
                         p[i]);
        }
    }

    return {status, true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    p.resize(n);
    for (int i = 0; i < n; ++i) {
        p[i] = inf.readLong();
    }

    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        long long low = inf.readLong();
        long long high = inf.readLong();
        edges[i] = {u - 1, v - 1, low, high};
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.hasFlow) {
        if (!participant.hasFlow) {
            quitf(_wa, "participant reported impossible but jury has a valid flow");
        }
        quitf(_ok, "valid flow");
    }

    if (participant.hasFlow) {
        quitf(_fail, "participant found a valid flow while jury reported impossible");
    }

    quitf(_ok, "both outputs report impossible");
}
