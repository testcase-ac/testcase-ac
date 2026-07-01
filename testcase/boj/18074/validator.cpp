#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000, "a_i");
    inf.readEoln();

    long long sum = accumulate(a.begin(), a.end(), 0LL);
    ensuref(sum <= 1000000LL, "sum of a_i must be at most 1000000, got %lld", sum);

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    inf.readInts(q, 1, static_cast<int>(sum), "t_i");
    inf.readEoln();

    inf.readEof();
}
