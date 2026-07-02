#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/rational.hpp>

#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;
using Rational = boost::rational<cpp_int>;

int n;

Rational absRational(const Rational& value) {
    return value < 0 ? -value : value;
}

Rational readFraction(InStream& stream, int opIndex) {
    long long p = stream.readLong(-1000000000000LL, 1000000000000LL,
                                  format("operation[%d].p", opIndex).c_str());
    long long q = stream.readLong(1, 1000000LL,
                                  format("operation[%d].q", opIndex).c_str());
    return Rational(cpp_int(p), cpp_int(q));
}

struct Claim {
    int operations;
};

Claim readClaim(InStream& stream) {
    int operationCount = stream.readInt(0, 2 * n, "Q");

    vector<Rational> rowAdd(n, Rational(0));
    vector<Rational> colAdd(n, Rational(0));

    for (int i = 1; i <= operationCount; ++i) {
        int type = stream.readInt(1, 2, format("operation[%d].type", i).c_str());
        if (type == 1) {
            int r = stream.readInt(1, n, format("operation[%d].r", i).c_str());
            rowAdd[r - 1] += readFraction(stream, i);
        } else {
            int c = stream.readInt(1, n, format("operation[%d].c", i).c_str());
            colAdd[c - 1] += readFraction(stream, i);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after operation list");
    }

    const Rational limit(cpp_int(n), cpp_int(4));
    vector<Rational> colAbs(n, Rational(0));

    for (int r = 0; r < n; ++r) {
        Rational rowAbs(0);
        for (int c = 0; c < n; ++c) {
            Rational value = (r <= c ? Rational(1) : Rational(0)) + rowAdd[r] + colAdd[c];
            Rational absoluteValue = absRational(value);
            rowAbs += absoluteValue;
            colAbs[c] += absoluteValue;
        }
        if (rowAbs > limit) {
            stream.quitf(_wa, "row %d has absolute sum greater than N/4", r + 1);
        }
    }

    for (int c = 0; c < n; ++c) {
        if (colAbs[c] > limit) {
            stream.quitf(_wa, "column %d has absolute sum greater than N/4", c + 1);
        }
    }

    return {operationCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 400, "N");

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);
    (void)jury;

    quitf(_ok, "valid beautiful matrix construction with %d operations", participant.operations);
}
