#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of swaps M: a natural number (>=1) and <=50
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Each of the next M lines: two integers X and Y, each in [1,3]
    for (int i = 0; i < M; i++) {
        char buf[20];
        sprintf(buf, "X_%d", i+1);
        int X = inf.readInt(1, 3, buf);
        inf.readSpace();
        sprintf(buf, "Y_%d", i+1);
        int Y = inf.readInt(1, 3, buf);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
