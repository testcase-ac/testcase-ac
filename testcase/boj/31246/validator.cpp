#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 1000000000LL, "A_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "B_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
