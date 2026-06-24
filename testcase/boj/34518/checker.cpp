#include "testlib.h"

#include <vector>
using namespace std;

struct Answer {
    bool impossible;
};

int n;

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "cell[1][1] or -1");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }

    vector<vector<int>> pos(n + 1);
    pos[first].push_back(0);

    for (int idx = 1; idx < 2 * n; ++idx) {
        int value = stream.readInt(1, n, format("cell[%d][%d]", idx / n + 1, idx % n + 1).c_str());
        pos[value].push_back(idx);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after grid");
    }

    for (int value = 1; value <= n; ++value) {
        if ((int)pos[value].size() != 2) {
            stream.quitf(_wa, "value %d appears %d times", value, (int)pos[value].size());
        }

        int r1 = pos[value][0] / n;
        int c1 = pos[value][0] % n;
        int r2 = pos[value][1] / n;
        int c2 = pos[value][1] % n;
        int dist = abs(r1 - r2) + abs(c1 - c2);

        if (dist != value) {
            stream.quitf(_wa, "value %d has distance %d", value, dist);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 5000, "N");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found a valid grid while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury provides a grid");
    }

    quitf(_ok, "valid grid");
}
