#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    // Read power values
    vector<int> power = inf.readInts(N, 1, 10000000, "power");
    inf.readEoln();

    inf.readEof();
}
