#include "testlib.h"

using namespace std;

using int64 = long long;

int64 n, p, r;

struct Answer {
    bool impossible;
    int64 k;
    int64 v;
};

int64 faultyRemainder(int64 k, int64 v) {
    int64 includedMultiplesOfP = n / p - (k % p == 0 ? 1 : 0);
    if (includedMultiplesOfP > 0) {
        return 0;
    }

    int64 product = v % p;
    for (int64 i = 1; i <= n; ++i) {
        if (i == k) {
            continue;
        }
        product = (product * (i % p)) % p;
    }
    return product;
}

Answer readAnswer(InStream& stream) {
    int64 first = stream.readLong(-1, n, "k");
    int64 second = stream.readLong(-1, max(n, p), "v");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after answer");
    }

    if (first == -1 && second == -1) {
        return {true, -1, -1};
    }
    if (first == -1 || second == -1) {
        stream.quitf(_wa, "impossible answer must be exactly -1 -1");
    }

    int64 k = first;
    int64 v = second;
    if (k < 2 || k > n) {
        stream.quitf(_wa, "fault index k=%lld is outside [2, %lld]", k, n);
    }
    if (v < 1 || v >= k) {
        stream.quitf(_wa, "fault value v=%lld is outside [1, %lld)", v, k);
    }

    int64 rem = faultyRemainder(k, v);
    if (rem != r) {
        stream.quitf(_wa,
                     "faulty factorial remainder is %lld, expected %lld",
                     rem,
                     r);
    }

    return {false, k, v};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong(2, (int64)1e18, "n");
    p = inf.readLong((int64)2, (int64)9999999, "p");
    r = inf.readLong(0, p - 1, "r");

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail,
              "participant found valid witness k=%lld v=%lld while jury reports impossible",
              participant.k,
              participant.v);
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible, but jury has a valid witness");
    }

    quitf(_ok, "valid witness k=%lld v=%lld", participant.k, participant.v);
}
