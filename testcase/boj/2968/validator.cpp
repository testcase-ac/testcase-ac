#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 1000000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 1000000, "C");
    inf.readEoln();

    // Compute maximum cells and check for overflow in long long
    long long maxCells = (long long)R * (long long)C;
    ensuref(maxCells >= 1, "Product R*C must be at least 1");

    // Read K
    long long K = inf.readLong(1LL, maxCells, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
