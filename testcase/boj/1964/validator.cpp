#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of steps
    long long N = inf.readLong(1LL, 10000000LL, "N");
    inf.readEoln();
    inf.readEof();

    return 0;
}
