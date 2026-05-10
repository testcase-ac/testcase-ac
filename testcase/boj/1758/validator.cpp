#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of people N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Each person's intended tip
    for (int i = 0; i < N; i++) {
        // tip_i is in [1, 100000]
        inf.readInt(1, 100000, "tip_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
