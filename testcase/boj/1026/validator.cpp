#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: natural number (1 to 50)
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read array A of size N, each element 0 to 100
    vector<int> A = inf.readInts(N, 0, 100, "A_i");
    inf.readEoln();

    // Read array B of size N, each element 0 to 100
    vector<int> B = inf.readInts(N, 0, 100, "B_i");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
