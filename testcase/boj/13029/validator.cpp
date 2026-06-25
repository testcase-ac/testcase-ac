#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 10000, "a_i");
    inf.readEoln();

    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    ensuref(sum <= 10000, "sum of a_i is %d, expected at most 10000", sum);

    inf.readEof();
    return 0;
}
