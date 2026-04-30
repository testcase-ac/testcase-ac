#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of desks
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Each desk has two grades Ai and Bi in [1,5]
    for (int i = 1; i <= N; i++) {
        // We allow exactly one space between the two integers
        inf.readInt(1, 5, "A_i");
        inf.readSpace();
        inf.readInt(1, 5, "B_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();

    return 0;
}
