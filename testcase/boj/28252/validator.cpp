#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 100000, "A_i");
    inf.readEoln();

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
    }
    ensuref(sum <= 100000, "sum of A_i must be at most 100000, got %lld", sum);

    inf.readEof();
}
