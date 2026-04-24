#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of integers
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the N integers, each between -1000 and 1000
    vector<int> a = inf.readInts(N, -1000, 1000, "a_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
