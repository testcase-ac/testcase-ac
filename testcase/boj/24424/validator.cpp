#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 150000, "N");
    inf.readEoln();

    int m = inf.readInt(1, n, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, m, "A_i");
        inf.readSpace();
        inf.readInt(-10000, 10000, "V_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
