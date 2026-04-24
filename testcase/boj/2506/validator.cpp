#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the number of problems
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read N results, each must be 0 or 1
    vector<int> results = inf.readInts(N, 0, 1, "result_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
