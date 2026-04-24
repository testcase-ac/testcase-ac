#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the N balloon heights
    vector<int> H = inf.readInts(n, 1, 1000000, "H_i");
    inf.readEoln();

    // No further constraints to check
    inf.readEof();
    return 0;
}
