#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 1000, "T_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
