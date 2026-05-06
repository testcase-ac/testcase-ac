#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Only one integer n on the first line
    long long n = inf.readLong(1LL, 10000000000000LL, "n");
    inf.readEoln();

    // No extra input
    inf.readEof();
}
