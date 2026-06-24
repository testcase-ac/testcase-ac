#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

struct Claim {
    bool impossible;
    long long m;
    long long k;
};

long long n;

long long parseNonNegativeInteger(InStream& stream, const string& token, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }
    for (char c : token) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            stream.quitf(_wa, "%s is not a non-negative integer: %s", name, token.c_str());
        }
    }

    long long value = 0;
    for (char c : token) {
        int digit = c - '0';
        if (value > (1000000000LL - digit) / 10) {
            stream.quitf(_wa, "%s is too large: %s", name, token.c_str());
        }
        value = value * 10 + digit;
    }
    return value;
}

Claim readClaim(InStream& stream) {
    string first = stream.readWord();
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true, 0, 0};
    }

    long long m = parseNonNegativeInteger(stream, first, "m");
    long long k = stream.readLong(0, 1000000000LL, "k");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after witness");
    }

    if (m * m - k * k != n) {
        stream.quitf(_wa, "m^2 - k^2 is %lld, expected %lld", m * m - k * k, n);
    }
    return {false, m, k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail,
              "participant found valid witness m=%lld k=%lld while jury claims impossible",
              participant.m,
              participant.k);
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible, but jury has witness m=%lld k=%lld", jury.m, jury.k);
    }

    quitf(_ok, "valid witness m=%lld k=%lld", participant.m, participant.k);
}
