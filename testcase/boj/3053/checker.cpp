#include "testlib.h"
using namespace std;

const double EPS = 1e-4;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = 0;
    double j = 0, p = 0;

    // We expect exactly two numbers in the jury answer (ans): the Euclidean area and the taxi area.
    // We'll read them one by one, and compare to the contestant output (ouf).
    while (!ans.seekEof()) {
        n++;
        j = ans.readDouble();
        p = ouf.readDouble();
        double diff = abs(j-p);
        if (diff > 0.0001) {
            quitf(_wa, "%d%s number differs - expected: '%.6f', found: '%.6f', error = '%.6f'",
                  n, englishEnding(n).c_str(), j, p, diff);
        }
    }

    // If we've read exactly two numbers and they both match within EPS, it's OK.
    quitf(_ok, "%d numbers", n);
}
