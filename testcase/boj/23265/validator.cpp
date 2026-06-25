#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400000, "n");
    inf.readSpace();
    inf.readInt(1, 1000000, "c");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "x");
    inf.readEoln();
    inf.readEof();
}
