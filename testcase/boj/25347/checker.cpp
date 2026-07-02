#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-6L;

struct Claim {
    long double blueError;
    long double redError;
};

int n;
long double qLimit;
vector<long double> redProb;
vector<long double> blueProb;

long double conditionalError(long double wrong, long double total) {
    if (total == 0.0L) {
        return 0.0L;
    }
    return wrong / total;
}

bool withinTolerance(long double expected, long double actual) {
    long double diff = fabsl(expected - actual);
    long double scale = max((long double)1.0L, fabsl(expected));
    return diff <= EPS || diff <= EPS * scale;
}

Claim readClaim(InStream& stream) {
    long double blueWrong = 0.0L;
    long double blueTotal = 0.0L;
    long double redWrong = 0.0L;
    long double redTotal = 0.0L;

    for (int i = 0; i < n; ++i) {
        double value = stream.readDouble(0.0, 1.0, format("p_%d", i + 1).c_str());
        long double p = value;

        blueWrong += redProb[i] * (1.0L - p);
        blueTotal += (redProb[i] + blueProb[i]) * (1.0L - p);
        redWrong += blueProb[i] * p;
        redTotal += (redProb[i] + blueProb[i]) * p;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after p_%d", n);
    }

    Claim claim{
        conditionalError(blueWrong, blueTotal),
        conditionalError(redWrong, redTotal),
    };

    if (claim.blueError > qLimit + EPS) {
        stream.quitf(_wa, "blue-answer error %.12Lf exceeds limit %.12Lf", claim.blueError, qLimit + EPS);
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    long double x = inf.readLong();
    long double y = inf.readLong();
    qLimit = x / y;

    vector<long double> r(n), b(n);
    long double redSum = 0.0L;
    long double blueSum = 0.0L;
    for (int i = 0; i < n; ++i) {
        r[i] = inf.readLong();
        redSum += r[i];
    }
    for (int i = 0; i < n; ++i) {
        b[i] = inf.readLong();
        blueSum += b[i];
    }

    redProb.resize(n);
    blueProb.resize(n);
    for (int i = 0; i < n; ++i) {
        redProb[i] = r[i] / redSum;
        blueProb[i] = b[i] / blueSum;
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.redError + EPS < jury.redError &&
        !withinTolerance(jury.redError, participant.redError)) {
        quitf(_fail,
              "participant red-answer error %.12Lf is better than jury %.12Lf",
              participant.redError,
              jury.redError);
    }

    if (!withinTolerance(jury.redError, participant.redError)) {
        quitf(_wa,
              "red-answer error %.12Lf differs from jury %.12Lf",
              participant.redError,
              jury.redError);
    }

    quitf(_ok,
          "blue-answer error %.12Lf, red-answer error %.12Lf",
          participant.blueError,
          participant.redError);
}
