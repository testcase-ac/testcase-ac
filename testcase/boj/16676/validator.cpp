#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 0 <= N <= 1e9
    long long N = inf.readLong(0LL, 1000000000LL, "N");
    inf.readEoln();

    // No further global constraints to check (answer always exists)
    inf.readEof();
    return 0;
}
