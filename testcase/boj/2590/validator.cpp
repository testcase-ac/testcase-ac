#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There are exactly 6 lines, each with one integer: the number of papers of size 1..6
    // Each number is between 0 and 100 inclusive.

    for (int i = 1; i <= 6; ++i) {
        int cnt = inf.readInt(0, 100, format("count_%d", i).c_str());
        inf.readEoln();
    }

    inf.readEof();
}
