#include "testlib.h"
#include <set>
#include <utility>

using namespace std;

int n, m;
set<pair<int, int>> graphEdges;

pair<int, int> edgeKey(int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    return {a, b};
}

struct Answer {
    int count;
};

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(0, m / 2, "K");
    stream.readEoln();

    set<pair<int, int>> usedEdges;
    for (int i = 0; i < k; ++i) {
        int u = stream.readInt(1, n, format("boomerang[%d].u", i + 1).c_str());
        stream.readSpace();
        int v = stream.readInt(1, n, format("boomerang[%d].v", i + 1).c_str());
        stream.readSpace();
        int w = stream.readInt(1, n, format("boomerang[%d].w", i + 1).c_str());
        stream.readEoln();

        if (u == w) {
            stream.quitf(_wa, "boomerang %d has equal endpoints u=w=%d", i + 1, u);
        }

        pair<int, int> first = edgeKey(u, v);
        pair<int, int> second = edgeKey(v, w);
        if (!graphEdges.count(first)) {
            stream.quitf(_wa, "boomerang %d uses missing edge (%d, %d)", i + 1, u, v);
        }
        if (!graphEdges.count(second)) {
            stream.quitf(_wa, "boomerang %d uses missing edge (%d, %d)", i + 1, v, w);
        }
        if (first == second) {
            stream.quitf(_wa, "boomerang %d reuses the same edge twice", i + 1);
        }
        if (!usedEdges.insert(first).second) {
            stream.quitf(_wa, "edge (%d, %d) is reused", first.first, first.second);
        }
        if (!usedEdges.insert(second).second) {
            stream.quitf(_wa, "edge (%d, %d) is reused", second.first, second.second);
        }
    }

    stream.readEof();
    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt();
        int v = inf.readInt();
        graphEdges.insert(edgeKey(u, v));
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.count < jury.count) {
        quitf(_wa, "jury has more boomerangs: jury=%d participant=%d", jury.count, participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail, "participant found more boomerangs: jury=%d participant=%d", jury.count, participant.count);
    }
    quitf(_ok, "answer=%d", participant.count);
}
