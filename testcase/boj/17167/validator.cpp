#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two positive integers A and B in [1, 10^18]
    long long A = inf.readLong(1LL, 1000000000000000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 1000000000000000000LL, "B");
    // Ensure the line ends here, and then the file ends immediately after
    inf.readEoln();
    inf.readEof();

    return 0;
}
