#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer K, must be between 2 and 1,000,000 inclusive
    int K = inf.readInt(2, 1000000, "K");
    
    // After K there must be exactly one newline, then EOF
    inf.readEoln();
    inf.readEof();
    
    return 0;
}
