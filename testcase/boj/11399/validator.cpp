#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of people N on the first line
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the N processing times P_i on the second line
    inf.readInts(N, 1, 1000, "P_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
