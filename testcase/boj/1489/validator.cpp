#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 1000, "A_i");
    inf.readEoln();

    // Read B_1 ... B_N
    vector<int> B = inf.readInts(N, 1, 1000, "B_i");
    inf.readEoln();

    inf.readEof();
}
