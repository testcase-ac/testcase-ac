#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of calls N: 1 <= N <= 20
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // Read N call durations: each between 1 and 10000
    vector<int> calls = inf.readInts(N, 1, 10000, "call_time");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
