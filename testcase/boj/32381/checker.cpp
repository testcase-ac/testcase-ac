#include "testlib.h"

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

long long n;
int q;
vector<long long> target;

struct Claim {
    bool impossible;
};

long long blackCells(long long blackRows, long long blackCols) {
    return blackRows * n + blackCols * n - 2LL * blackRows * blackCols;
}

void flipIndex(unordered_set<int>& blackSet, long long& blackCount, int index) {
    auto it = blackSet.find(index);
    if (it == blackSet.end()) {
        blackSet.insert(index);
        ++blackCount;
    } else {
        blackSet.erase(it);
        --blackCount;
    }
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken();
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    unordered_set<int> blackRows;
    unordered_set<int> blackCols;
    long long rowCount = 0;
    long long colCount = 0;

    for (int i = 1; i <= q; ++i) {
        string kind = (i == 1 ? first : stream.readToken());
        if (kind != "R" && kind != "C") {
            stream.quitf(_wa, "operation %d has invalid kind '%s'", i, kind.c_str());
        }

        int index = stream.readInt(1, (int)n, format("operation[%d].index", i).c_str());
        if (kind == "R") {
            flipIndex(blackRows, rowCount, index);
        } else {
            flipIndex(blackCols, colCount, index);
        }

        long long current = blackCells(rowCount, colCount);
        if (current != target[i]) {
            stream.quitf(_wa,
                         "after operation %d black cells is %lld, expected %lld",
                         i,
                         current,
                         target[i]);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d operations", q);
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong();
    q = inf.readInt();
    target.assign(q + 1, 0);
    for (int i = 1; i <= q; ++i) {
        target[i] = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury provides a witness");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant provides a valid witness while jury reports impossible");
    }

    quitf(_ok, "valid %s claim", participant.impossible ? "impossible" : "witness");
}
