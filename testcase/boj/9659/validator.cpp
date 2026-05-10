#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of stones, between 1 and 1e12
    long long N = inf.readLong(1LL, 1000000000000LL, "N");

    // Ensure N is the only token on its line
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
