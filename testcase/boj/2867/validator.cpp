#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 300000, "N");
    inf.readEoln();

    // Read the sequence, one element per line
    for (int i = 0; i < N; i++) {
        // Each element is a positive integer <= 1e8
        inf.readInt(1, 100000000, "a_i");
        inf.readEoln();
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
