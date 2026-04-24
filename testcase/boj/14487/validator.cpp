#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of villages
    int n = inf.readInt(1, 50000, "n");
    inf.readEoln();

    // Read the n movement costs
    inf.readInts(n, 1, 1000, "v_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
