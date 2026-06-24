#include "testlib.h"

using namespace std;

struct Claim {
    bool impossible;
};

long long n;

bool equals128(__int128 lhs, __int128 rhs) {
    return lhs == rhs;
}

Claim readClaim(InStream& stream) {
    long long a = stream.readLong(-4000000000000000000LL, 4000000000000000000LL, "a or -1");

    if (a == -1 && stream.seekEof()) {
        return {true};
    }

    long long b = stream.readLong(-4000000000000000000LL, 4000000000000000000LL, "b");
    long long c = stream.readLong(-4000000000000000000LL, 4000000000000000000LL, "c");
    long long d = stream.readLong(-4000000000000000000LL, 4000000000000000000LL, "d");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after factorization");
    }

    if (!equals128((__int128)a * c, n)) {
        stream.quitf(_wa, "a*c must be %lld, found %lld*%lld", n, a, c);
    }
    if (!equals128((__int128)b * d, -((__int128)n + 2))) {
        stream.quitf(_wa, "b*d must be -%lld, found %lld*%lld", n + 2, b, d);
    }
    if (!equals128((__int128)a * d + (__int128)b * c, n + 1)) {
        stream.quitf(_wa, "a*d+b*c must be %lld", n + 1);
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong(1LL, 2000000LL, "n");

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid factorization while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible while jury has a valid factorization");
    }

    quitf(_ok, "valid factorization");
}
