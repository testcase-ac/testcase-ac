#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 500000, "a_i");
    inf.readEoln();

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        ensuref(sum <= 500000, "sum of a_i exceeds 500000 at index %d", i + 1);
    }

    inf.readEof();
}
