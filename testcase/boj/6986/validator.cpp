#include "testlib.h"
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(3, 100000, "N");
    inf.readSpace();
    // K <= floor(N/2) - 1
    int maxK = N / 2 - 1;
    ensuref(maxK >= 0, "Computed max K is negative for N=%d", N);
    int K = inf.readInt(0, maxK, "K");
    inf.readEoln();

    // Read N scores, each a real number between 0.0 and 10.0 inclusive,
    // given with exactly one digit after the decimal point.
    for (int i = 0; i < N; i++) {
        // Token must be either D.D where D is [0-9], or 10.0
        // We use a regex to enforce exactly one decimal digit.
        string s = inf.readToken("[0-9]\\.[0-9]|10\\.0", "score");
        // Convert to double and verify range
        double v = atof(s.c_str());
        ensuref(v >= 0.0 && v <= 10.0,
                "Score %d parsed as %f is out of range [0.0,10.0]", i, v);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
