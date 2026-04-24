#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: size of the enclosure (columns), must be between 1 and 100000
    long long N = inf.readLong(1LL, 100000LL, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
