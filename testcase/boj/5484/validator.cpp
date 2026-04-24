#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read garden dimensions
    int l = inf.readInt(1, 250, "l");
    inf.readSpace();
    int w = inf.readInt(1, 250, "w");
    inf.readEoln();

    // Read number of roses and required roses per rectangle
    int n = inf.readInt(2, 5000, "n");
    inf.readSpace();
    // k must satisfy 1 <= k <= floor(n/2)
    int k = inf.readInt(1, n / 2, "k");
    inf.readEoln();

    // Read positions of the n roses
    for (int i = 0; i < n; i++) {
        int li = inf.readInt(1, l, "l_i");
        inf.readSpace();
        int wi = inf.readInt(1, w, "w_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
