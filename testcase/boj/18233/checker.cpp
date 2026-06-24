#include "testlib.h"

#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    vector<int> gifts;
};

int n, p;
long long e;
vector<int> lowerBound;
vector<int> upperBound;

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, 1000000LL, "gift[1] or -1");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    vector<int> gifts(n);
    gifts[0] = static_cast<int>(first);
    for (int i = 1; i < n; ++i) {
        gifts[i] = stream.readInt(0, 1000000, format("gift[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after assignment");
    }

    int selected = 0;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        if (gifts[i] == 0) {
            continue;
        }
        ++selected;
        if (gifts[i] < lowerBound[i] || gifts[i] > upperBound[i]) {
            stream.quitf(_wa,
                         "gift[%d]=%d is outside allowed range [%d, %d]",
                         i + 1,
                         gifts[i],
                         lowerBound[i],
                         upperBound[i]);
        }
        sum += gifts[i];
    }

    if (selected != p) {
        stream.quitf(_wa, "selected %d members instead of %d", selected, p);
    }
    if (sum != e) {
        stream.quitf(_wa, "gift sum is %lld instead of %lld", sum, e);
    }

    return {false, gifts};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    p = inf.readInt();
    e = inf.readLong();

    lowerBound.resize(n);
    upperBound.resize(n);
    for (int i = 0; i < n; ++i) {
        lowerBound[i] = inf.readInt();
        upperBound[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid assignment while jury claims impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid assignment but participant claims impossible");
    }

    quitf(_ok, "valid assignment");
}
