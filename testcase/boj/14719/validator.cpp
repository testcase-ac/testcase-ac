#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions H and W
    int H = inf.readInt(1, 500, "H");
    inf.readSpace();
    int W = inf.readInt(1, 500, "W");
    inf.readEoln();

    // Read the heights array of size W, each between 0 and H
    inf.readInts(W, 0, H, "h_i");
    inf.readEoln();

    // No further lines; ensure end of file
    inf.readEof();
    return 0;
}
