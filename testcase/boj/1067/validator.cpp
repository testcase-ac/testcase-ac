#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 60000, "N");
    inf.readEoln();

    inf.readInts(n, 0, 99, "X_i");
    inf.readEoln();

    inf.readInts(n, 0, 99, "Y_i");
    inf.readEoln();

    inf.readEof();
}
