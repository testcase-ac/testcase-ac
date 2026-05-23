#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int p = inf.readInt(2, 300000, "P");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(1, 6, "string_i");
        inf.readSpace();
        inf.readInt(1, p, "fret_i");
        inf.readEoln();
    }

    inf.readEof();
}
