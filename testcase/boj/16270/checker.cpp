#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

const long long MAX_VALUE = 1000000000000000000LL;

long long squarefreeKernel(long long a, long long b) {
    long long x = a / gcd(a, b);
    long long y = b / gcd(a, b);
    long long result = 1;

    for (long long p = 2; p * p <= x; ++p) {
        int parity = 0;
        while (x % p == 0) {
            x /= p;
            parity ^= 1;
        }
        while (y % p == 0) {
            y /= p;
            parity ^= 1;
        }
        if (parity) {
            result *= p;
        }
    }

    for (long long p = 2; p * p <= y; ++p) {
        int parity = 0;
        while (y % p == 0) {
            y /= p;
            parity ^= 1;
        }
        if (parity) {
            result *= p;
        }
    }

    if (x > 1) {
        result *= x;
    }
    if (y > 1) {
        result *= y;
    }

    return result;
}

struct Claim {
    vector<long long> sums;
};

Claim readClaim(InStream& stream, const vector<long long>& kernels) {
    Claim claim;
    claim.sums.reserve(kernels.size());

    for (int tc = 0; tc < int(kernels.size()); ++tc) {
        long long first = stream.readLong(1, MAX_VALUE, format("a'[%d]", tc + 1).c_str());
        long long second = stream.readLong(1, MAX_VALUE, format("b'[%d]", tc + 1).c_str());

        if (first > MAX_VALUE / second || first * second != kernels[tc]) {
            stream.quitf(_wa,
                         "case %d: pair (%lld, %lld) is not reachable, expected product %lld",
                         tc + 1,
                         first,
                         second,
                         kernels[tc]);
        }

        claim.sums.push_back(first + second);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d case(s)", int(kernels.size()));
    }
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt(1, 500, "t");
    vector<long long> kernels;
    kernels.reserve(t);
    for (int i = 0; i < t; ++i) {
        long long a = inf.readLong(1, 1000000000LL, "a");
        long long b = inf.readLong(1, 1000000000LL, "b");
        kernels.push_back(squarefreeKernel(a, b));
    }

    Claim jury = readClaim(ans, kernels);
    Claim participant = readClaim(ouf, kernels);

    for (int i = 0; i < t; ++i) {
        if (participant.sums[i] > jury.sums[i]) {
            quitf(_wa,
                  "case %d: jury has better sum %lld, participant has %lld",
                  i + 1,
                  jury.sums[i],
                  participant.sums[i]);
        }
        if (participant.sums[i] < jury.sums[i]) {
            quitf(_fail,
                  "case %d: participant found better sum %lld than jury sum %lld",
                  i + 1,
                  participant.sums[i],
                  jury.sums[i]);
        }
    }

    quitf(_ok, "%d case(s) accepted", t);
}
