#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k from the first line
    long long n = inf.readLong(1LL, 100000000000000000LL, "n");
    inf.readSpace();
    int k = inf.readInt(1, 40, "k");
    inf.readEoln();

    // No further input, so check for EOF
    inf.readEof();
}
