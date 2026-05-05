#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 3 lines, each with a positive integer < 100
    int weights[3];
    for (int i = 0; i < 3; ++i) {
        weights[i] = inf.readInt(1, 99, "weight");
        inf.readEoln();
    }

    inf.readEof();
}
