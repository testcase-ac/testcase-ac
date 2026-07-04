#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<int> l = inf.readInts(n, 1, 1000000, "l_i");
    inf.readEoln();

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += l[i];
    }
    ensuref(sum <= 1000000, "sum of l_i must be at most 1000000, got %lld", sum);

    inf.readEof();
}
