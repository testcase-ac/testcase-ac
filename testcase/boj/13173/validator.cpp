#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 100, "P");
    inf.readEoln();

    int q = inf.readInt(0, p, "Q");
    inf.readEoln();

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    int k = inf.readInt(0, n, "K");
    inf.readEoln();

    inf.readEof();
    return 0;
}
