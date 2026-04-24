#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read N positive integers a_i, each < 1e9
    vector<int> a = inf.readInts(N, 1, 999999999, "a_i");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read M positive integers b_i, each < 1e9
    vector<int> b = inf.readInts(M, 1, 999999999, "b_i");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
