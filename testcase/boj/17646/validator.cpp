#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read the single natural number n in the range [1, 1e18].
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readEoln();
    
    // No extra data allowed.
    inf.readEof();
    return 0;
}
