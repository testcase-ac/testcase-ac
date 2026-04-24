#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the sequence of heights
    vector<int> P = inf.readInts(N, 1, 1000, "P_i");
    inf.readEoln();

    // Ensure no extra data
    inf.readEof();
    return 0;
}
