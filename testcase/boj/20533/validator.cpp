#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(7, 500000, "N");
    inf.readEoln();

    // Read A_i values
    vector<int> A = inf.readInts(N, 1, 200000000, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();

    return 0;
}
