#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 1000000000000000LL, "A_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "B_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
