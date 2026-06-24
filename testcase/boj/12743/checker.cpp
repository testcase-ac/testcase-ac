#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-2;
const double DOUBLE_LIMIT = 1e100;

int n;
int x, y;
vector<int> ga, gb, w;

struct Answer {
    double value;
    double a;
    double b;
    double computedValue;
};

Answer readAnswer(InStream& stream) {
    double value = stream.readDouble(-DOUBLE_LIMIT, DOUBLE_LIMIT, "value");
    stream.readEoln();
    double a = stream.readDouble(-DOUBLE_LIMIT, DOUBLE_LIMIT, "A");
    stream.readSpace();
    double b = stream.readDouble(-DOUBLE_LIMIT, DOUBLE_LIMIT, "B");
    stream.readEoln();
    stream.readEof();

    if (!isfinite(value) || !isfinite(a) || !isfinite(b)) {
        stream.quitf(_wa, "all output values must be finite");
    }
    if (a < -EPS || b < -EPS) {
        stream.quitf(_wa, "amounts must be non-negative: A=%.12f B=%.12f", a, b);
    }

    a = max(0.0, a);
    b = max(0.0, b);

    for (int i = 0; i < n; ++i) {
        double used = ga[i] * a + gb[i] * b;
        double slack = (ga[i] + gb[i]) * EPS + 1e-7;
        if (used > w[i] + slack) {
            stream.quitf(_wa,
                         "material %d exceeds supply: used=%.12f limit=%d",
                         i + 1,
                         used,
                         w[i]);
        }
    }

    double computedValue = x * a + y * b;
    if (!doubleCompare(computedValue, value, EPS)) {
        stream.quitf(_wa,
                     "claimed value %.12f does not match A=%.12f B=%.12f objective %.12f",
                     value,
                     a,
                     b,
                     computedValue);
    }

    return {value, a, b, computedValue};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    x = inf.readInt();
    y = inf.readInt();

    ga.resize(n);
    gb.resize(n);
    w.resize(n);
    for (int i = 0; i < n; ++i) ga[i] = inf.readInt();
    for (int i = 0; i < n; ++i) gb[i] = inf.readInt();
    for (int i = 0; i < n; ++i) w[i] = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!doubleCompare(jury.value, participant.value, EPS) ||
        !doubleCompare(jury.a, participant.a, EPS) ||
        !doubleCompare(jury.b, participant.b, EPS)) {
        if (participant.computedValue > jury.computedValue &&
            !doubleCompare(jury.computedValue, participant.computedValue, EPS)) {
            quitf(_fail,
                  "participant found better feasible value: jury=%.12f participant=%.12f",
                  jury.computedValue,
                  participant.computedValue);
        }
        quitf(_wa,
              "expected value/A/B %.12f %.12f %.12f, found %.12f %.12f %.12f",
              jury.value,
              jury.a,
              jury.b,
              participant.value,
              participant.a,
              participant.b);
    }

    quitf(_ok,
          "value/A/B %.12f %.12f %.12f are within tolerance",
          participant.value,
          participant.a,
          participant.b);
}
