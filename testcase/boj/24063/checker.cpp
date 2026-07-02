#include "testlib.h"

#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    long long c;
};

struct Answer {
    bool impossible;
    long long cost;
};

int n;
long long modValue;
vector<Edge> edges;

long long residue(long long value) {
    return value % modValue;
}

Answer readAnswer(InStream& stream) {
    long long first = stream.readLong(-1, 1000000000000000000LL, "first output value");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, 0};
    }

    vector<long long> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        value[i] = stream.readLong(1, modValue, format("A'_%d", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    for (const Edge& edge : edges) {
        long long got = (residue(value[edge.a]) + residue(value[edge.b])) % modValue;
        if (got != edge.c) {
            stream.quitf(_wa,
                         "constraint (%d, %d, %lld) is violated: got %lld",
                         edge.a,
                         edge.b,
                         edge.c,
                         got);
        }
    }

    return {false, first};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 200000, "N");
    int edgeCount = inf.readInt(1, 1000000, "M");
    modValue = inf.readLong(2, 1000000000LL, "m");

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000, format("X_%d", i).c_str());
    }

    edges.reserve(edgeCount);
    for (int i = 0; i < edgeCount; ++i) {
        int a = inf.readInt(1, n, format("a_%d", i + 1).c_str());
        int b = inf.readInt(1, n, format("b_%d", i + 1).c_str());
        long long c = inf.readLong(0, modValue - 1, format("c_%d", i + 1).c_str());
        edges.push_back({a, b, c});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid assignment while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury has cost %lld", jury.cost);
    }
    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant found a lower cost than jury: participant=%lld jury=%lld",
              participant.cost,
              jury.cost);
    }
    if (participant.cost > jury.cost) {
        quitf(_wa,
              "participant cost is higher than jury: participant=%lld jury=%lld",
              participant.cost,
              jury.cost);
    }

    quitf(_ok, "valid assignment with cost %lld", participant.cost);
}
