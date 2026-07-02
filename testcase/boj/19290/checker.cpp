#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

const long long MAX_LABEL = 1000000000LL;

int n;
vector<int> canChange;
vector<pair<int, int>> edges;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, MAX_LABEL, "first token");

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true};
    }

    if (first != n) {
        stream.quitf(_wa, "first line is %lld, expected n=%d", first, n);
    }

    vector<long long> label(n + 1, -1);
    set<long long> usedLabels;
    long long totalXor = first;

    stream.readEoln();
    for (int i = 0; i < n - 1; ++i) {
        long long outU = stream.readLong(1LL, MAX_LABEL, format("edge[%d].u", i + 1).c_str());
        long long outV = stream.readLong(1LL, MAX_LABEL, format("edge[%d].v", i + 1).c_str());
        stream.readEoln();

        int u = edges[i].first;
        int v = edges[i].second;

        if (label[u] == -1) {
            label[u] = outU;
        } else if (label[u] != outU) {
            stream.quitf(_wa, "vertex %d has inconsistent labels %lld and %lld",
                         u, label[u], outU);
        }

        if (label[v] == -1) {
            label[v] = outV;
        } else if (label[v] != outV) {
            stream.quitf(_wa, "vertex %d has inconsistent labels %lld and %lld",
                         v, label[v], outV);
        }

        totalXor ^= outU;
        totalXor ^= outV;
    }
    stream.readEof();

    for (int vertex = 1; vertex <= n; ++vertex) {
        if (label[vertex] == -1) {
            stream.quitf(_wa, "vertex %d does not appear in the output tree", vertex);
        }
        if (!canChange[vertex] && label[vertex] != vertex) {
            stream.quitf(_wa, "fixed vertex %d has label %lld", vertex, label[vertex]);
        }
        if (!usedLabels.insert(label[vertex]).second) {
            stream.quitf(_wa, "label %lld is used by more than one vertex", label[vertex]);
        }
    }

    if (totalXor != 0) {
        stream.quitf(_wa, "xor of printed numbers is %lld, expected 0", totalXor);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    canChange.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        canChange[i] = inf.readInt();
    }

    edges.resize(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges[i] = {u, v};
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid relabeling while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury provides a valid relabeling but participant claims impossible");
    }

    quitf(_ok, "valid relabeling");
}
