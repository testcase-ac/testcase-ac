#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    vector<int> k = inf.readInts(n, -n, n, "k_i");
    (void)k;
    inf.readEoln();

    inf.readEof();
}
