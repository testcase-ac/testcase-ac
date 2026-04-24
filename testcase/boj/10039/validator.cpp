#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 5 students, one score per line
    for (int i = 1; i <= 5; i++) {
        // Read score_i: must be integer in [0,100]
        char name[20];
        sprintf(name, "score_%d", i);
        int s = inf.readInt(0, 100, name);
        // Check that it's a multiple of 5
        ensuref(s % 5 == 0, "%s is not a multiple of 5: %d", name, s);
        // After each score, there must be exactly one end-of-line
        inf.readEoln();
    }

    // No extra data after the five lines
    inf.readEof();
    return 0;
}
