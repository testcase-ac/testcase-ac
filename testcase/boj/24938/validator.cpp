#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000, "A_i");
    inf.readEoln();

    long long sum = 0;
    for (int value : a) {
        sum += value;
    }
    ensuref(sum % n == 0, "sum of A_i must be divisible by N: sum=%lld, N=%d", sum, n);

    inf.readEof();
}
