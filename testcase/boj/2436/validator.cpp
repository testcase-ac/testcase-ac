#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    
    // Read G and L
    int G = inf.readInt(2, 100000000, "G");
    inf.readSpace();
    int L = inf.readInt(2, 100000000, "L");
    inf.readEoln();

    // Validate that L is a multiple of G (necessary and sufficient for existence)
    ensuref(L % G == 0, "LCM %d is not divisible by GCD %d", L, G);

    inf.readEof();
    return 0;
}
