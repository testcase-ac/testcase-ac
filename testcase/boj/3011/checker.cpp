#include "testlib.h"
#include <vector>
#include <cstdint>
#include <cstdlib>
using namespace std;

int N;
vector<long long> P;
long long A, B;

// Reads an answer X from the given stream (ans or ouf), checks it's valid,
// computes and returns its score = min_i |X - P[i]|.
// On invalid X, quits with _wa for ouf or _fail for ans.
long long readAns(InStream &stream) {
    long long X = stream.readLong(A, B, "daughter's name");
    if (X % 2 == 0)
        stream.quitf(_wa, "daughter's name %lld is not odd", X);
    long long mind = llabs(X - P[0]);
    for (int i = 1; i < N; i++) {
        long long d = llabs(X - P[i]);
        if (d < mind) mind = d;
    }
    return mind;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    N = inf.readInt(1, 100, "N");
    P.resize(N);
    for (int i = 0; i < N; i++) {
        P[i] = inf.readLong(1, 1000000000LL, format("P[%d]", i+1).c_str());
    }
    A = inf.readLong(1, 1000000000LL, "A");
    B = inf.readLong(1, 1000000000LL, "B");

    // Read jury and participant answers
    long long jscore = readAns(ans);
    long long pscore = readAns(ouf);

    // Compare scores
    if (jscore > pscore) {
        quitf(_wa,
              "participant's name yields distance = %lld, but maximum possible = %lld",
              pscore, jscore);
    } else if (jscore == pscore) {
        quitf(_ok, "distance = %lld", pscore);
    } else {
        // participant found a strictly better answer than jury
        quitf(_fail,
              "participant's distance = %lld is greater than jury's = %lld",
              pscore, jscore);
    }
}
