#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-2;
const double NEG_EPS = 1e-9;

int n;
double xValue, yValue;
vector<double> ga, gb, available;

struct Claim {
    double value;
    double amountA;
    double amountB;
};

bool withinError(double expected, double actual) {
    return doubleCompare(expected, actual, EPS);
}

double amountTolerance(double amount) {
    return EPS * max(1.0, fabs(amount));
}

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.value = stream.readDouble(-1e100, 1e100, "value");
    claim.amountA = stream.readDouble(-1e100, 1e100, "amountA");
    claim.amountB = stream.readDouble(-1e100, 1e100, "amountB");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the three required numbers");
    }

    if (claim.value < -NEG_EPS) {
        stream.quitf(_wa, "claimed value %.12f is negative", claim.value);
    }
    if (claim.amountA < -NEG_EPS || claim.amountB < -NEG_EPS) {
        stream.quitf(_wa,
                     "negative amount: A=%.12f B=%.12f",
                     claim.amountA,
                     claim.amountB);
    }

    claim.amountA = max(0.0, claim.amountA);
    claim.amountB = max(0.0, claim.amountB);

    for (int i = 0; i < n; ++i) {
        double used = ga[i] * claim.amountA + gb[i] * claim.amountB;
        double tolerance = ga[i] * amountTolerance(claim.amountA) +
                           gb[i] * amountTolerance(claim.amountB) +
                           EPS * max(1.0, available[i]);
        if (used > available[i] + tolerance) {
            stream.quitf(_wa,
                         "material %d exceeds availability: used %.12f available %.12f",
                         i + 1,
                         used,
                         available[i]);
        }
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    xValue = inf.readDouble();
    yValue = inf.readDouble();

    ga.resize(n);
    gb.resize(n);
    available.resize(n);

    for (int i = 0; i < n; ++i) ga[i] = inf.readDouble();
    for (int i = 0; i < n; ++i) gb[i] = inf.readDouble();
    for (int i = 0; i < n; ++i) available[i] = inf.readDouble();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.value > jury.value && !withinError(jury.value, participant.value)) {
        quitf(_fail,
              "participant found better feasible value: jury=%.12f participant=%.12f",
              jury.value,
              participant.value);
    }
    if (!withinError(jury.value, participant.value)) {
        quitf(_wa,
              "expected value %.12f, found %.12f, error %.12f",
              jury.value,
              participant.value,
              doubleDelta(jury.value, participant.value));
    }
    if (!withinError(jury.amountA, participant.amountA) ||
        !withinError(jury.amountB, participant.amountB)) {
        quitf(_wa,
              "expected amounts A=%.12f B=%.12f, found A=%.12f B=%.12f",
              jury.amountA,
              jury.amountB,
              participant.amountA,
              participant.amountB);
    }

    quitf(_ok,
          "value %.12f with A=%.12f B=%.12f",
          participant.value,
          participant.amountA,
          participant.amountB);
}
