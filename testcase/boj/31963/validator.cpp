#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 250000, "N");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(n, 1, 1000000, "A");
    inf.readEoln();

    inf.readEof();
    return 0;
}
