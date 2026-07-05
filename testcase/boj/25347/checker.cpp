#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-6L;

struct Claim {
    long double blueBagWrong;
    long double redBagWrong;
};

int n;
long double qLimit;
vector<long double> redProb;
vector<long double> blueProb;

bool withinTolerance(long double expected, long double actual) {
    long double diff = fabsl(expected - actual);
    long double scale = max((long double)1.0L, fabsl(expected));
    return diff <= EPS || diff <= EPS * scale;
}

Claim readClaim(InStream& stream) {
    long double blueBagWrong = 0.0L;
    long double redBagWrong = 0.0L;

    for (int i = 0; i < n; ++i) {
        double value = stream.readDouble(0.0, 1.0, format("p_%d", i + 1).c_str());
        long double p = value;

        blueBagWrong += blueProb[i] * p;
        redBagWrong += redProb[i] * (1.0L - p);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after p_%d", n);
    }

    if (blueBagWrong > qLimit + EPS) {
        stream.quitf(_wa,
                     "blue-bag wrong probability %.12Lf exceeds limit %.12Lf",
                     blueBagWrong,
                     qLimit + EPS);
    }

    return {blueBagWrong, redBagWrong};
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

    if (participant.redBagWrong + EPS < jury.redBagWrong &&
        !withinTolerance(jury.redBagWrong, participant.redBagWrong)) {
        quitf(_fail,
              "participant red-bag wrong probability %.12Lf is better than jury %.12Lf",
              participant.redBagWrong,
              jury.redBagWrong);
    }

    if (!withinTolerance(jury.redBagWrong, participant.redBagWrong)) {
        quitf(_wa,
              "red-bag wrong probability %.12Lf differs from jury %.12Lf",
              participant.redBagWrong,
              jury.redBagWrong);
    }

    quitf(_ok,
          "blue-bag wrong probability %.12Lf, red-bag wrong probability %.12Lf",
          participant.blueBagWrong,
          participant.redBagWrong);
}
