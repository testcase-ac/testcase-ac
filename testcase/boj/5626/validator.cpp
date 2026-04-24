#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read heights h_i
    vector<int> h = inf.readInts(N, -1, 10000, "h_i");
    inf.readEoln();

    // No further constraints implied by problem statement
    inf.readEof();
    return 0;
}
