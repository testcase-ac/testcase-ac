#include "testlib.h"

#include <vector>

using namespace std;

int n;

struct Claim {
    bool impossible;
};

bool isComposite(int x) {
    if (x <= 3) {
        return false;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return true;
        }
    }
    return false;
}

Claim readClaim(InStream& stream, TResult invalidVerdict) {
    int first = stream.readInt(-1, n, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(invalidVerdict, "extra output after -1");
        }
        return {true};
    }
    if (first == 0) {
        stream.quitf(invalidVerdict, "permutation value 0 is outside [1, %d]", n);
    }

    vector<int> used(n + 1, 0);
    long long prefix = first;
    used[first] = 1;
    if (!isComposite((int)prefix)) {
        stream.quitf(invalidVerdict, "prefix sum at position 1 is %lld, which is not composite", prefix);
    }

    for (int i = 2; i <= n; ++i) {
        int value = stream.readInt(1, n, format("p[%d]", i).c_str());
        if (used[value]) {
            stream.quitf(invalidVerdict, "value %d appears more than once", value);
        }
        used[value] = 1;
        prefix += value;
        if (!isComposite((int)prefix)) {
            stream.quitf(invalidVerdict, "prefix sum at position %d is %lld, which is not composite", i, prefix);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidVerdict, "extra output after permutation");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "n");
    inf.readEoln();
    inf.readEof();

    Claim jury = readClaim(ans, _fail);
    Claim participant = readClaim(ouf, _wa);

    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid permutation while jury reports -1");
    }
    if (!jury.impossible && participant.impossible) {
        quitf(_wa, "jury provides a valid permutation, but participant reports -1");
    }

    quitf(_ok, "valid output");
}
