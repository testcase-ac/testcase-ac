#include "testlib.h"

#include <vector>

using namespace std;

struct Placement {
    int n;
};

Placement readPlacement(InStream& stream, int n) {
    vector<char> occupied((n + 1) * (n + 1), 0);
    vector<char> mainDiag(2 * n + 1, 0);
    vector<char> antiDiag(2 * n + 2, 0);

    for (int i = 0; i < n; ++i) {
        int r = stream.readInt(1, n, format("r[%d]", i + 1).c_str());
        int c = stream.readInt(1, n, format("c[%d]", i + 1).c_str());
        stream.readEoln();

        int cell = r * (n + 1) + c;
        if (occupied[cell]) {
            stream.quitf(_wa, "bishop %d repeats cell (%d, %d)", i + 1, r, c);
        }
        occupied[cell] = 1;
        mainDiag[r - c + n] = 1;
        antiDiag[r + c] = 1;
    }

    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            if (!mainDiag[r - c + n] && !antiDiag[r + c]) {
                stream.quitf(_wa, "cell (%d, %d) is not covered", r, c);
            }
        }
    }

    return {n};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<int> ns(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        ns[caseIndex] = inf.readInt();
    }

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        readPlacement(ans, ns[caseIndex]);
    }
    ans.readEof();

    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        readPlacement(ouf, ns[caseIndex]);
    }
    ouf.readEof();

    quitf(_ok, "all placements cover their boards");
}
