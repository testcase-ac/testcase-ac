#include "testlib.h"

#include <vector>

using namespace std;

long long n;

struct Claim {
    bool impossible;
};

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, 64LL, "K or -1");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first < 3) {
        stream.quitf(_wa, "K must be at least 3, found %lld", first);
    }

    int k = (int)first;
    vector<long long> seq(k);
    __int128 sum = 0;
    for (int i = 0; i < k; ++i) {
        seq[i] = stream.readLong(1, n, format("term[%d]", i + 1).c_str());
        sum += seq[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    if (sum != n) {
        stream.quitf(_wa, "sequence sum is not N");
    }
    if (seq[1] % seq[0] != 0) {
        stream.quitf(_wa, "second term is not an integer multiple of first term");
    }

    long long ratio = seq[1] / seq[0];
    if (ratio <= 1) {
        stream.quitf(_wa, "common ratio must be greater than 1");
    }

    for (int i = 2; i < k; ++i) {
        if ((__int128)seq[i - 1] * ratio != seq[i]) {
            stream.quitf(_wa, "term[%d] does not match common ratio %lld", i + 1, ratio);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readEoln();
    inf.readEof();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.impossible) {
        if (participant.impossible) {
            quitf(_wa, "jury has a valid sequence but participant printed -1");
        }
        quitf(_ok, "valid geometric sequence");
    }

    if (participant.impossible) {
        quitf(_ok, "both outputs claim impossible");
    }
    quitf(_fail, "participant found a valid sequence while jury printed -1");
}
