#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the decimal number N
    long long N = inf.readLong(-2000000000LL, 2000000000LL, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
