#include "testlib.h"
#include <cstdlib>
#include <set>
#include <string>
#include <vector>
using namespace std;

int n, m;
set<pair<int, int>> edges;

struct Claim {
    bool impossible;
    vector<int> target;
};

int parseVertexToken(InStream& stream, const string& token, int index) {
    char* end = nullptr;
    long value = strtol(token.c_str(), &end, 10);
    if (*end != '\0') {
        stream.quitf(_wa, "target[%d] is not an integer: %s", index, token.c_str());
    }
    if (value < 1 || value > n) {
        stream.quitf(_wa, "target[%d]=%ld is outside [1,%d]", index, value, n);
    }
    return (int)value;
}

bool canSee(int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    return edges.count({a, b}) != 0;
}

Claim readClaim(InStream& stream) {
    string first = stream.readWord();
    if (first == "Impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after Impossible");
        }
        return {true, {}};
    }

    vector<int> target(n + 1);
    target[1] = parseVertexToken(stream, first, 1);
    for (int i = 2; i <= n; ++i) {
        target[i] = stream.readInt(1, n, format("target[%d]", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    vector<int> hitCount(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (!canSee(i, target[i])) {
            stream.quitf(_wa, "player %d cannot see target %d", i, target[i]);
        }
        ++hitCount[target[i]];
    }
    for (int i = 1; i <= n; ++i) {
        if (hitCount[i] != 1) {
            stream.quitf(_wa, "player %d is hit %d times instead of once", i, hitCount[i]);
        }
    }

    return {false, target};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.insert({a, b});
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim Impossible");
        }
        quitf(_fail, "participant found a valid assignment while jury says Impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid assignment but participant says Impossible");
    }

    quitf(_ok, "valid assignment");
}
