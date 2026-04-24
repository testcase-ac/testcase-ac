#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the sequence A of length N, each between 1 and 1000
    vector<int> A = inf.readInts(n, 1, 1000, "A_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
