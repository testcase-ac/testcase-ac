#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readLong(1LL, 1000000000LL, "X");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "S");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "c_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
