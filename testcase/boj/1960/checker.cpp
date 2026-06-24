#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int n;
vector<int> rowCount;
vector<int> colCount;

struct Claim {
    bool possible;
};

Claim readClaim(InStream& stream) {
    int verdict = stream.readInt(-1, 1, "verdict");
    if (verdict != -1 && verdict != 1) {
        stream.quitf(_wa, "verdict must be -1 or 1, found %d", verdict);
    }

    if (verdict == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible verdict");
        }
        return {false};
    }

    vector<int> colSeen(n, 0);
    for (int i = 0; i < n; ++i) {
        string row = stream.readToken(format("[01]{%d}", n), format("row[%d]", i + 1).c_str());
        int rowSeen = 0;
        for (int j = 0; j < n; ++j) {
            int bit = row[j] - '0';
            rowSeen += bit;
            colSeen[j] += bit;
        }
        if (rowSeen != rowCount[i]) {
            stream.quitf(_wa, "row %d has %d ones, expected %d", i + 1, rowSeen, rowCount[i]);
        }
    }

    for (int j = 0; j < n; ++j) {
        if (colSeen[j] != colCount[j]) {
            stream.quitf(_wa, "column %d has %d ones, expected %d", j + 1, colSeen[j], colCount[j]);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after matrix");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    rowCount.resize(n);
    colCount.resize(n);
    for (int i = 0; i < n; ++i) {
        rowCount[i] = inf.readInt();
    }
    for (int i = 0; i < n; ++i) {
        colCount[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "participant reported impossible but jury provided a valid matrix");
        }
        quitf(_ok, "valid matrix");
    }

    if (participant.possible) {
        quitf(_fail, "participant provided a valid matrix while jury reported impossible");
    }

    quitf(_ok, "both outputs report impossible");
}
