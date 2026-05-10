#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of integers
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read the N integers, each between 0 and 10000 inclusive
    vector<int> a = inf.readInts(N, 0, 10000, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
