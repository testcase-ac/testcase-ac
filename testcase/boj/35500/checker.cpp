#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

struct Answer {
    long long coprimePairs;
};

int n;
long long k;

Answer readAnswer(InStream& stream) {
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = stream.readLong(2LL, 1000000000000000000LL,
                               format("A[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }

    long long pairs = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (gcd(a[i], a[j]) == 1) {
                ++pairs;
            }
        }
    }

    if (pairs != k) {
        stream.quitf(_wa, "sequence has %lld coprime pairs, expected %lld", pairs, k);
    }

    return {pairs};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readLong();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.coprimePairs != jury.coprimePairs) {
        quitf(_wa, "participant claim differs from jury claim");
    }

    quitf(_ok, "sequence has %lld coprime pairs", participant.coprimePairs);
}
