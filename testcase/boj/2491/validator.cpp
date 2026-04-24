#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the sequence of N digits (0 to 9) all on one line, separated by spaces
    for (int i = 0; i < N; i++) {
        inf.readInt(0, 9, "a_i");
        if (i + 1 < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
