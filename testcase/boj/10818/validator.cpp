#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of integers
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the N integers, each between -1e6 and 1e6
    vector<int> a = inf.readInts(N, -1000000, 1000000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
