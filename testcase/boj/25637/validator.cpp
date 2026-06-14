#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, n, "a_i");
    inf.readEoln();

    long long sum = 0;
    for (int x : a) {
        sum += x;
    }
    ensuref(sum == n, "sum of a_i must be n: sum=%lld, n=%d", sum, n);

    inf.readEof();
}
