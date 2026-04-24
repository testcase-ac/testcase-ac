#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of rounds N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each round, read A and B
    for (int i = 1; i <= N; i++) {
        int A = inf.readInt(1, 99, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, 99, "B_i");
        inf.readEoln();
    }

    // No extra characters
    inf.readEof();
    return 0;
}
