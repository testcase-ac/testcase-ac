#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n1 = inf.readInt(0, 10000, "n_1");
    inf.readSpace();
    int n2 = inf.readInt(0, 10000, "n_2");
    inf.readSpace();
    int n12 = inf.readInt(0, min(n1, n2), "n_12");
    inf.readEoln();

    inf.readEof();
    return 0;
}
