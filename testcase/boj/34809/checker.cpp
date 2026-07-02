#include "testlib.h"

#include <vector>

using namespace std;

const int LIMIT = 100000000;

int n;
vector<long long> a;

bool isPrime(long long x) {
    if (x < 2) {
        return false;
    }
    if (x % 2 == 0) {
        return x == 2;
    }
    for (long long d = 3; d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

struct Claim {
    bool impossible;
    long long p;
};

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, (long long)LIMIT - 1, "p");

    if (first == -1) {
        stream.readEoln();
        stream.readEof();
        return {true, -1};
    }

    long long p = first;
    if (!isPrime(p)) {
        stream.quitf(_wa, "p=%lld is not prime", p);
    }

    for (int i = 0; i < n; ++i) {
        if (p <= a[i]) {
            stream.quitf(_wa, "p=%lld is not greater than a[%d]=%lld", p, i + 1, a[i]);
        }
    }

    stream.readEoln();
    for (int i = 0; i < n; ++i) {
        long long x = stream.readLong(0, p - 1, format("x[%d]", i + 1).c_str());
        stream.readSpace();
        long long y = stream.readLong(0, p - 1, format("y[%d]", i + 1).c_str());
        stream.readEoln();

        long long lhs = a[i] % p;
        long long rhs = (x * x + y * y) % p;
        if (lhs != rhs) {
            stream.quitf(_wa,
                         "a[%d]=%lld is not congruent to %lld^2+%lld^2 modulo %lld",
                         i + 1,
                         a[i],
                         x,
                         y,
                         p);
        }
    }
    stream.readEof();

    return {false, p};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        a.push_back(inf.readLong());
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant found valid p=%lld while jury reports impossible", participant.p);
    }

    if (participant.impossible) {
        quitf(_wa, "jury has valid p=%lld but participant reports impossible", jury.p);
    }

    quitf(_ok, "valid p=%lld", participant.p);
}
