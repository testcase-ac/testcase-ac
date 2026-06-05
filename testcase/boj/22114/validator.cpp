#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 100, "K");
    inf.readEoln();

    inf.readInts(n - 1, 1, 100, "L_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
