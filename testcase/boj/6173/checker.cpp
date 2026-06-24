#include "testlib.h"

#include <vector>

using namespace std;

int n, colorCount;
vector<int> required;

struct PairingClaim {
    bool valid;
};

PairingClaim readClaim(InStream& stream, TResult invalidVerdict) {
    vector<int> remaining = required;

    for (int i = 0; i < n / 2; ++i) {
        int a = stream.readInt(1, colorCount, format("pair[%d].first", i + 1).c_str());
        stream.readSpace();
        int b = stream.readInt(1, colorCount, format("pair[%d].second", i + 1).c_str());
        stream.readEoln();

        if (a == b) {
            stream.quitf(invalidVerdict, "pair %d uses color %d twice", i + 1, a);
        }
        --remaining[a];
        --remaining[b];
        if (remaining[a] < 0) {
            stream.quitf(invalidVerdict, "color %d is used too many times by pair %d", a, i + 1);
        }
        if (remaining[b] < 0) {
            stream.quitf(invalidVerdict, "color %d is used too many times by pair %d", b, i + 1);
        }
    }

    stream.readEof();

    for (int color = 1; color <= colorCount; ++color) {
        if (remaining[color] != 0) {
            stream.quitf(invalidVerdict,
                         "color %d has %d unused pearls after all pairs",
                         color,
                         remaining[color]);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    colorCount = inf.readInt();
    required.assign(colorCount + 1, 0);
    for (int color = 1; color <= colorCount; ++color) {
        required[color] = inf.readInt();
    }

    PairingClaim jury = readClaim(ans, _fail);
    PairingClaim participant = readClaim(ouf, _wa);

    if (jury.valid && participant.valid) {
        quitf(_ok, "valid pairing with %d pairs", n / 2);
    }
    quitf(_fail, "unreachable checker state");
}
