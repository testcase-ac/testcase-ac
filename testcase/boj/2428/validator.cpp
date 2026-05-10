#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of submissions
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the sizes of the submissions
    vector<int> sizes = inf.readInts(N, 1, 100000000, "size(F_i)");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
