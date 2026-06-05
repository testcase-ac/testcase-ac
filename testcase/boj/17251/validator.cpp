#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();
    ensuref(n % 2 == 0, "n must be even: %d", n);

    vector<int> strengths = inf.readInts(n, 1, 10000, "strength");
    (void)strengths;
    inf.readEoln();

    inf.readEof();
}
