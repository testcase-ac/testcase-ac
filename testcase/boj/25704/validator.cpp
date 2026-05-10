#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of stamps
    int N = inf.readInt(0, 30, "N");
    inf.readEoln();

    // Read P: price of the item
    int P = inf.readInt(100, 50000, "P");
    ensuref(P % 100 == 0, "P (%d) must be a multiple of 100", P);
    inf.readEoln();

    inf.readEof();
}
