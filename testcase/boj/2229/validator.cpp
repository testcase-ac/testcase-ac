#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read N scores
    inf.readInts(N, 0, 10000, "score");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
