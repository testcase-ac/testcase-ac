#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readEoln();

    ensuref(!(n == 1 && m == 1), "N and M must not both be 1");

    inf.readEof();
    return 0;
}
