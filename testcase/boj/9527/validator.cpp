#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B on the first line
    long long A = inf.readLong(1LL, 10000000000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(A, 10000000000000000LL, "B");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
