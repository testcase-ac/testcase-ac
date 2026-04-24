#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read sequence A of length N
    vector<int> A = inf.readInts(N, 1, 100, "A_i");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read sequence B of length M
    vector<int> B = inf.readInts(M, 1, 100, "B_i");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
