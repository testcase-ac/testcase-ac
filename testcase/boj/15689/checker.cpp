#include "testlib.h"
#include <cmath>
#include <string>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the single expected and actual probabilities
    double juryProb = ans.readDouble();
    double userProb = ouf.readDouble();

    // Compare with absolute or relative error EPS
    if (!doubleCompare(juryProb, userProb, EPS)) {
        quitf(_wa,
              "probabilities differ - expected: '%.7f', found: '%.7f', error = '%.7f'",
              juryProb, userProb, doubleDelta(juryProb, userProb));
    }
    // If there's any extra output from the contestant, that's a format error
    ouf.skipBlanks();
    if (!ouf.eof()) {
        quitf(_pe, "extra data after the probability");
    }

    quitf(_ok, "probability = '%.7f'", userProb);
    return 0;
}
