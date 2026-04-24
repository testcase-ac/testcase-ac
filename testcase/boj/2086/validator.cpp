#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a and b on the first line
    // We assume 1 <= a <= b <= 1e18 as reasonable bounds for long long inputs
    long long a = inf.readLong(1LL, 1000000000000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(a, 1000000000000000000LL, "b"); // ensures b >= a
    inf.readEoln();

    inf.readEof();
    return 0;
}
