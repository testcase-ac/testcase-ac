#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and T
    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int T = inf.readInt(1, 500, "T");
    inf.readEoln();

    // Read the n job times
    vector<int> times = inf.readInts(n, 1, 100, "time_i");
    inf.readEoln();

    // No further constraints or global properties to check
    inf.readEof();
    return 0;
}
