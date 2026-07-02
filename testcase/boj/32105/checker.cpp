#include "testlib.h"

#include <vector>

using namespace std;

struct Answer {
    int pairs;
};

int n;
vector<bool> semiprime;

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(0, n / 2, "K");
    stream.readEoln();

    vector<bool> used(n + 1, false);
    for (int i = 0; i < k; ++i) {
        int a = stream.readInt(1, n, format("pair[%d].first", i + 1).c_str());
        stream.readSpace();
        int b = stream.readInt(1, n, format("pair[%d].second", i + 1).c_str());
        stream.readEoln();

        if (a == b) {
            stream.quitf(_wa, "pair %d uses number %d twice", i + 1, a);
        }
        if (used[a]) {
            stream.quitf(_wa, "number %d is reused", a);
        }
        if (used[b]) {
            stream.quitf(_wa, "number %d is reused", b);
        }
        if (!semiprime[a + b]) {
            stream.quitf(_wa, "pair %d has sum %d, which is not a product of two primes", i + 1, a + b);
        }

        used[a] = true;
        used[b] = true;
    }

    stream.readEof();
    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100000, "N");
    inf.readEoln();
    inf.readEof();

    vector<int> smallestPrime(2 * n + 1, 0);
    for (int i = 2; i <= 2 * n; ++i) {
        if (smallestPrime[i] != 0) {
            continue;
        }
        for (long long j = i; j <= 2LL * n; j += i) {
            if (smallestPrime[j] == 0) {
                smallestPrime[j] = i;
            }
        }
    }

    semiprime.assign(2 * n + 1, false);
    for (int x = 4; x <= 2 * n; ++x) {
        int p = smallestPrime[x];
        int q = x / p;
        semiprime[x] = (p > 1 && x % p == 0 && q >= 2 && smallestPrime[q] == q);
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.pairs < jury.pairs) {
        quitf(_wa, "participant used fewer pairs: expected %d, found %d", jury.pairs, participant.pairs);
    }
    if (participant.pairs > jury.pairs) {
        quitf(_fail, "participant found more pairs than jury: expected %d, found %d", jury.pairs, participant.pairs);
    }

    quitf(_ok, "accepted %d pairs", participant.pairs);
}
