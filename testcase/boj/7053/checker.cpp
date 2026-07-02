#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    vector<int> switches;
};

int n;
vector<int> outputBits;

void validateSwitches(InStream& stream, const vector<int>& switches) {
    for (int tick = 0; tick < n; ++tick) {
        int next = 0;
        for (int pos = 0; pos < n; ++pos) {
            if (switches[pos] == 1) {
                next ^= outputBits[tick + n - 1 - pos];
            }
        }
        if (next != outputBits[tick + n]) {
            stream.quitf(_wa,
                         "switch vector does not reproduce output bit %d: expected %d, got %d",
                         tick + n + 1,
                         outputBits[tick + n],
                         next);
        }
    }
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken();
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    vector<int> switches(n);
    if (first == "0" || first == "1") {
        switches[0] = first[0] - '0';
    } else {
        stream.quitf(_wa, "switch[1] must be 0, 1, or -1");
    }

    for (int i = 1; i < n; ++i) {
        switches[i] = stream.readInt(0, 1, format("switch[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after switch vector");
    }
    validateSwitches(stream, switches);
    return {false, switches};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 750, "N");
    outputBits.resize(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        outputBits[i] = inf.readInt(0, 1, format("output[%d]", i + 1).c_str());
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid switch vector while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible but jury provides a valid switch vector");
    }

    quitf(_ok, "valid switch vector");
}
