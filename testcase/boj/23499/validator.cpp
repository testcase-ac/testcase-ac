#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int maxK = n * (n - 1) / 2;
    int k = inf.readInt(0, maxK, "k");
    inf.readSpace();
    int x = inf.readInt(2, 1000, "x");
    inf.readEoln();

    inf.readEof();
    return 0;
}
