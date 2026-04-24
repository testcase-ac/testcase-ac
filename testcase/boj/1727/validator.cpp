#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Read men's personality values
    vector<int> men = inf.readInts(n, 1, 1000000, "a_i");
    inf.readEoln();

    // Read women's personality values
    vector<int> women = inf.readInts(m, 1, 1000000, "b_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
