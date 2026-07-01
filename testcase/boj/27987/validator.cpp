#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    vector<int> k = inf.readInts(n, 1, 100000, "K_i");
    inf.readEoln();

    long long sum = accumulate(k.begin(), k.end(), 0LL);
    ensuref(sum <= 100000, "sum(K) must be at most 100000, got %lld", sum);

    inf.readEof();
}
