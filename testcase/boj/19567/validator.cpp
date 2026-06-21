#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "a_i");
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "b_i");
        inf.readSpace();
        inf.readLong(0LL, 2000000000LL, "c_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
