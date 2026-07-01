#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(2, 10, "K");
    inf.readSpace();
    int n = inf.readInt(k, 202000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 499999, "A_i");
    inf.readEoln();

    long long sum = accumulate(a.begin(), a.end(), 0LL);
    ensuref(sum <= 500000, "sum of A_i must be at most 500000, got %lld", sum);

    inf.readEof();
}
