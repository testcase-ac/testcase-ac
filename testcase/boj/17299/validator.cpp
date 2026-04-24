#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the array A of size N on a single line, with spaces between elements
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 1000000, "A_i");
        if (i + 1 < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
