#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read H, W, N, M
    int H = inf.readInt(1, 50000, "H");
    inf.readSpace();
    int W = inf.readInt(1, 50000, "W");
    inf.readSpace();
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50000, "M");
    inf.readEoln();

    // No further constraints to check (all are basic ranges, no global property)
    // Check for extra input
    inf.readEof();
}
