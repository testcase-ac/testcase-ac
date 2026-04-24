#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-9;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the jury's answer and the contestant's answer
    double jury_ans = ans.readDouble();
    double user_ans = ouf.readDouble();

    // Compare within the required precision
    if (!doubleCompare(jury_ans, user_ans, EPS)) {
        quitf(_wa,
              "expected: '%.10f', found: '%.10f', error = '%.10f'",
              jury_ans, user_ans, doubleDelta(jury_ans, user_ans));
    }

    // If we're here, it's correct
    quitf(_ok,
          "expected: '%.10f', found: '%.10f', error = '%.10f'",
          jury_ans, user_ans, doubleDelta(jury_ans, user_ans));
}
