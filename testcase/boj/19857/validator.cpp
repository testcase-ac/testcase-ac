#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<long long> c = inf.readLongs(n, 0LL, 1000000000LL, "c_i");
    inf.readEoln();

    long long total = 0;
    for (long long x : c) {
        total += x;
    }
    ensuref(total >= 1, "sum of c_i must be at least 1");

    inf.readEof();
}
