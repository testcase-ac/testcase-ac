#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readSpace();
    long long r = inf.readLong(1LL, 100000000000000LL, "R");
    inf.readEoln();

    vector<int> s = inf.readInts(n, 1, 1000000000, "s_i");
    inf.readEoln();

    inf.readEof();
}
