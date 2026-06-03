#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 100000, "H");
    inf.readEoln();

    vector<int> w = inf.readInts(h, 1, 100000, "W_i");
    inf.readEoln();

    long long total = 0;
    for (int i = 0; i < h; ++i) {
        total += w[i];
    }
    ensuref(total <= 100000, "sum W_i must be at most 100000, got %lld", total);

    long long c = inf.readLong(0LL, 100000LL, "C");
    inf.readSpace();
    long long d = inf.readLong(0LL, 100000LL, "D");
    inf.readEoln();
    ensuref(c + d == total, "C + D must equal sum W_i: %lld + %lld != %lld", c, d, total);

    inf.readEof();
}
