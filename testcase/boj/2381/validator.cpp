#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-1000000, 1000000, "x");
        inf.readSpace();
        inf.readInt(-1000000, 1000000, "y");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
