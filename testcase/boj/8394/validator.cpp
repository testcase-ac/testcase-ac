#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read number of people n: 1 ≤ n ≤ 10,000,000
    int n = inf.readInt(1, 10000000, "n");
    // Expect end of line after n
    inf.readEoln();
    // No more input
    inf.readEof();
    return 0;
}
