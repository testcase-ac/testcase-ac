#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 10000, "a_i");
        inf.readSpace();
        inf.readInt(0, 10000, "b_i");
        inf.readSpace();
        inf.readInt(0, 10000, "c_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
