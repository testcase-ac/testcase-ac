#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N: number of stones
    long long N = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readEoln();
    inf.readEof();
    return 0;
}
