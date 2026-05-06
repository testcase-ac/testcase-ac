#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two fame values N and M in the specified range
    long long N = inf.readLong(-2000000000LL, 2000000000LL, "N");
    inf.readSpace();
    long long M = inf.readLong(-2000000000LL, 2000000000LL, "M");
    inf.readEoln();
    
    // No other input should follow
    inf.readEof();
    return 0;
}
