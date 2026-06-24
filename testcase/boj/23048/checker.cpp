#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Answer {
    int k;
};

int n;
vector<int> minPrime;
vector<int> primes;

void buildSieve() {
    minPrime.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (minPrime[i] == 0) {
            minPrime[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > n || p > minPrime[i]) {
                break;
            }
            minPrime[v] = p;
        }
    }
}

vector<int> distinctPrimeFactors(int x) {
    vector<int> factors;
    while (x > 1) {
        int p = minPrime[x];
        factors.push_back(p);
        while (x % p == 0) {
            x /= p;
        }
    }
    return factors;
}

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(1, n, "K");
    vector<int> color(n + 1);
    for (int i = 1; i <= n; ++i) {
        color[i] = stream.readInt(1, k, format("color[%d]", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after color list");
    }

    vector<int> owner(k + 1, 0);
    auto claimForcedColor = [&](int value, const char* label) {
        int c = color[value];
        if (owner[c] != 0) {
            stream.quitf(_wa,
                         "color %d is used by both forced values %d and %s %d",
                         c,
                         owner[c],
                         label,
                         value);
        }
        owner[c] = value;
    };

    claimForcedColor(1, "value");
    for (int p : primes) {
        claimForcedColor(p, "prime");
    }

    for (int x = 2; x <= n; ++x) {
        if (minPrime[x] == x) {
            continue;
        }
        bool matchesFactorColor = false;
        for (int p : distinctPrimeFactors(x)) {
            if (color[x] == color[p]) {
                matchesFactorColor = true;
                break;
            }
        }
        if (!matchesFactorColor) {
            stream.quitf(_wa,
                         "composite %d has color %d, which is not used by any prime divisor",
                         x,
                         color[x]);
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 500000, "N");
    buildSieve();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.k > jury.k) {
        quitf(_wa, "participant uses more colors than jury: participant=%d jury=%d", participant.k, jury.k);
    }
    if (participant.k < jury.k) {
        quitf(_fail, "participant uses fewer valid colors than jury: participant=%d jury=%d", participant.k, jury.k);
    }
    quitf(_ok, "valid coloring with %d colors", participant.k);
}
