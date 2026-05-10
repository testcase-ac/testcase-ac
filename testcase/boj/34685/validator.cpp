#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k
    int k = inf.readInt(-10000000, 10000000, "k");
    inf.readEoln();

    ensuref(k != 0, "k must not be zero, but got %d", k);

    inf.readEof();
}
