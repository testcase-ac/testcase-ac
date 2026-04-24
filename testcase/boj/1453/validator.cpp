#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of customers N: 0 <= N <= 100
    int N = inf.readInt(0, 100, "N");
    inf.readEoln();

    // Read N desired seat numbers, each between 1 and 100
    inf.readInts(N, 1, 100, "seat");
    inf.readEoln();

    inf.readEof();
    return 0;
}
