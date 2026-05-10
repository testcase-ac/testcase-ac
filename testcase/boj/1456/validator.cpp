#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B
    long long A = inf.readLong(1LL, 100000000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(A, 100000000000000LL, "B");
    inf.readEoln();

    inf.readEof();
}
