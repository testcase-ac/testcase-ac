#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> initial;

struct Claim {
    bool impossible;
    int operations;
};

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, 100, "Q or -1");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, 0};
    }

    int q = first;
    vector<int> state = initial;
    for (int i = 0; i < q; ++i) {
        int l = stream.readInt(1, n, format("l[%d]", i + 1).c_str());
        int r = stream.readInt(1, n, format("r[%d]", i + 1).c_str());
        if (l > r) {
            stream.quitf(_wa, "operation %d has l=%d greater than r=%d", i + 1, l, r);
        }
        reverse(state.begin() + l - 1, state.begin() + r);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operations");
    }

    for (int i = 0; i < n; ++i) {
        if (state[i] != i + 1) {
            stream.quitf(_wa, "operations do not sort the toys: position %d has %d", i + 1, state[i]);
        }
    }

    return {false, q};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    initial.resize(n);
    for (int i = 0; i < n; ++i) {
        initial[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant provided a valid sorting sequence while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury provides %d operations", jury.operations);
    }

    quitf(_ok, "valid sorting sequence with %d operations", participant.operations);
}
