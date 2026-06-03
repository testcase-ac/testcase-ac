#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readEoln();
    ensuref(n % 2 == 0, "N must be even: %d", n);

    vector<int> cards = inf.readInts(n, 1, 10000, "X");
    inf.readEoln();

    inf.readEof();
    return 0;
}
