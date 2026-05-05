#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of trees
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read desired heights
    inf.readInts(N, 0, 10000, "h");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
