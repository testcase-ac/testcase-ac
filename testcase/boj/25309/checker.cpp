#include "testlib.h"

#include <vector>
using namespace std;

int n, k;

struct Claim {
    bool impossible;
    vector<long long> primes;
};

bool isPrime(long long value) {
    if (value < 2) return false;
    if (value == 2 || value == 3) return true;
    if (value % 2 == 0 || value % 3 == 0) return false;
    for (long long d = 5; d * d <= value; d += 6) {
        if (value % d == 0 || value % (d + 2) == 0) return false;
    }
    return true;
}

Claim readClaim(InStream& stream) {
    long long first = stream.readLong(-1LL, 100000000LL, "answer[1]");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }

    vector<long long> primes;
    primes.push_back(first);
    for (int i = 1; i < k; ++i) {
        primes.push_back(stream.readLong(-1LL, 100000000LL, format("answer[%d]", i + 1).c_str()));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after decomposition");
    }

    long long sum = 0;
    for (int i = 0; i < k; ++i) {
        long long value = primes[i];
        if (value < 2) {
            stream.quitf(_wa, "answer[%d]=%lld is not a prime", i + 1, value);
        }
        if (!isPrime(value)) {
            stream.quitf(_wa, "answer[%d]=%lld is not a prime", i + 1, value);
        }
        sum += value;
    }

    if (sum != n) {
        stream.quitf(_wa, "prime sum is %lld, expected %d", sum, n);
    }

    return {false, primes};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid decomposition while jury output is -1");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible, but jury has a valid decomposition");
    }

    quitf(_ok, "valid decomposition");
}
