#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and S
    int N = inf.readInt(1, 20, "N");
    inf.readSpace();
    int S = inf.readInt(-1000000, 1000000, "S");
    inf.readEoln();

    // Read sequence of N integers
    vector<int> a = inf.readInts(N, -100000, 100000, "a");
    inf.readEoln();

    // No additional global checks required
    inf.readEof();
    return 0;
}
