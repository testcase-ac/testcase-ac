#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the sequence A of length N
    vector<int> A = inf.readInts(N, -1000000000, 1000000000, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
