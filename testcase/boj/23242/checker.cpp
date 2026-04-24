#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-4;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read jury's correct answer
    double j = ans.readDouble();
    // Read participant's answer
    double p = ouf.readDouble();

    // Check absolute error
    double diff = fabs(j - p);
    if (diff > EPS) {
        quitf(_wa,
              "wrong answer: expected %.6f, found %.6f, abs error = %.6f > %.6f",
              j, p, diff, EPS);
    }

    // Optionally ensure there's no extra output
    ouf.readEof();

    quitf(_ok, "ok: answer = %.6f, abs error = %.6f", p, diff);
}
