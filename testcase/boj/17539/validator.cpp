#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line containing N
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readEoln();

    // No further input
    inf.readEof();
}
