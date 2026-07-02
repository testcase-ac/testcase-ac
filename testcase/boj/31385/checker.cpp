#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> primes;

struct Claim {
    bool impossible;
};

int divisorCount(int value) {
    int remaining = value;
    int result = 1;
    for (int prime : primes) {
        if (prime * prime > remaining) {
            break;
        }
        if (remaining % prime != 0) {
            continue;
        }
        int exponent = 0;
        while (remaining % prime == 0) {
            remaining /= prime;
            ++exponent;
        }
        result *= exponent + 1;
    }
    if (remaining > 1) {
        result *= 2;
    }
    return result;
}

void buildPrimes() {
    int limit = static_cast<int>(sqrt(300LL * n)) + 2;
    vector<bool> composite(limit + 1, false);
    for (int i = 2; i <= limit; ++i) {
        if (!composite[i]) {
            primes.push_back(i);
            if (1LL * i * i <= limit) {
                for (long long j = 1LL * i * i; j <= limit; j += i) {
                    composite[static_cast<int>(j)] = true;
                }
            }
        }
    }
}

Claim readClaim(InStream& stream) {
    string first = stream.readWord("[A-Za-z0-9+-]+", "first output token");
    if (first == "Impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after Impossible");
        }
        return {true};
    }

    int prefixSum = 0;
    long long firstValue = stringToLongLong(stream, first.c_str());
    if (firstValue < 1 || firstValue > 300) {
        stream.quitf(_wa, "a[1]=%lld is outside [1, 300]", firstValue);
    }
    prefixSum += static_cast<int>(firstValue);

    for (int i = 2; i <= n; ++i) {
        int value = stream.readInt(1, 300, format("a[%d]", i).c_str());
        prefixSum += value;
        int divisors = divisorCount(prefixSum);
        if (divisors != value) {
            stream.quitf(_wa,
                         "prefix sum through a[%d] is %d and has %d divisors, not %d",
                         i,
                         prefixSum,
                         divisors,
                         value);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }
    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 100000, "n");
    if (!inf.seekEof()) {
        quitf(_fail, "extra data after n in input");
    }
    buildPrimes();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim Impossible");
        }
        quitf(_fail, "participant provided a valid sequence while jury says Impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant says Impossible, but jury provides a valid sequence");
    }
    quitf(_ok, "valid sequence");
}
