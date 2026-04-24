#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 1000, "M");
    inf.readEoln();

    // Read the array A of size N
    inf.readInts(N, 0, 1000000000, "A_i");
    inf.readEoln();

    // No further global constraints to check; just ensure EOF
    inf.readEof();

    return 0;
}
