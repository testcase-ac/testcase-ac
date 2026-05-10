#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of places N
    int N = inf.readInt(2, 2500, "N");
    inf.readEoln();

    // Read the number of pebbles at each place
    inf.readInts(N, 1, 100000000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
