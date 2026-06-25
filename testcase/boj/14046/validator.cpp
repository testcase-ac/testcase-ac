#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000LL, "T");
    inf.readEoln();

    string initial = inf.readToken("[01]{3,100000}", "initial");
    ensuref(int(initial.size()) == n,
            "initial configuration length is %d, expected %d",
            int(initial.size()), n);
    inf.readEoln();

    inf.readEof();
    return 0;
}
