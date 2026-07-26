#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    long long r = inf.readLong(1LL, 1000000000LL, "R");
    inf.readSpace();
    long long m = inf.readLong(n, 1000000000LL, "M");
    inf.readEoln();
    ensuref(m <= 2LL * r * n, "M must not exceed 2RN");

    vector<int> positions = inf.readInts(n, 0, (int)m - 1, "x_i");
    inf.readEoln();
    inf.readEof();

    sort(positions.begin(), positions.end());
    ensuref(adjacent_find(positions.begin(), positions.end()) == positions.end(),
            "robot positions must be distinct");
}
