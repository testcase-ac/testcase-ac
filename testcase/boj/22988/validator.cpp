#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    long long x = inf.readLong(1LL, 1000000000000000000LL, "x");
    inf.readEoln();

    vector<long long> c = inf.readLongs(n, 0LL, x, "c_i");
    inf.readEoln();

    inf.readEof();
}
