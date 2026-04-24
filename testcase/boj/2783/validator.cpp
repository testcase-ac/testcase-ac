#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read Seven25 price info
    int X = inf.readInt(1, 100, "X");
    inf.readSpace();
    int Y = inf.readInt(1, 1000, "Y");
    inf.readEoln();

    // Read number of other convenience stores
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read each store's price info
    for (int i = 0; i < N; i++) {
        // Dynamic naming for clearer error messages
        char bufX[20], bufY[20];
        sprintf(bufX, "X_%d", i+1);
        sprintf(bufY, "Y_%d", i+1);

        int Xi = inf.readInt(1, 100, bufX);
        inf.readSpace();
        int Yi = inf.readInt(1, 1000, bufY);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
