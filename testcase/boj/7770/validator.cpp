#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of available blocks
    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readEoln();

    inf.readEof();
    return 0;
}
