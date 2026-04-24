#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer T (in decimal) with bounds [1, 10000]
    int T = inf.readInt(1, 10000, "T");
    // After T, there must be exactly one end-of-line
    inf.readEoln();
    // And nothing else in the file
    inf.readEof();

    return 0;
}
