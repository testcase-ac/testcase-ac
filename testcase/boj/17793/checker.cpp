#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the correct answer and the contestant's answer
    double jury_ans = ans.readDouble();
    double part_ans = ouf.readDouble();

    // Check absolute error
    double diff = fabs(jury_ans - part_ans);
    if (diff > EPS) {
        quitf(_wa,
              "expected: '%.9f', found: '%.9f', error = '%.9f'",
              jury_ans, part_ans, diff);
    }

    // Ensure there's no extra output
    ouf.readEof();

    quitf(_ok, "answer = '%.9f'", part_ans);
}
