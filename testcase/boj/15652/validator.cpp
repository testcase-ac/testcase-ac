#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M on the first line
    int N = inf.readInt(1, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, 8, "M");
    inf.readEoln();

    // Validate the implied constraint M <= N
    ensuref(M <= N, "M must be less than or equal to N, but M=%d and N=%d", M, N);

    // No more input
    inf.readEof();
    return 0;
}
