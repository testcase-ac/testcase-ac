#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read Subin's and sibling's positions: N and K
    // Both should be integers in [0, 100000]
    int N = inf.readInt(0, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 100000, "K");
    inf.readEoln();
    
    // No further constraints (the solution must compute the answer).
    inf.readEof();
    return 0;
}
