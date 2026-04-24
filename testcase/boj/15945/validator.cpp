#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read the sequence A_1 ... A_n
    vector<int> A = inf.readInts(n, -1000000000, 1000000000, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
