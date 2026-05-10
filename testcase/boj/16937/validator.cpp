#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read paper size H, W
    int H = inf.readInt(1, 100, "H");
    inf.readSpace();
    int W = inf.readInt(1, 100, "W");
    inf.readEoln();

    // Read number of stickers N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read each sticker's dimensions
    for (int i = 0; i < N; i++) {
        char bufR[16], bufC[16];
        snprintf(bufR, sizeof(bufR), "R_%d", i+1);
        snprintf(bufC, sizeof(bufC), "C_%d", i+1);
        int R = inf.readInt(1, 100, bufR);
        inf.readSpace();
        int C = inf.readInt(1, 100, bufC);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
