#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 100, "a_i");
    inf.readEoln();

    vector<int> b = inf.readInts(n, 1, 100, "b_i");
    inf.readEoln();

    int sum_a = accumulate(a.begin(), a.end(), 0);
    int sum_b = accumulate(b.begin(), b.end(), 0);
    ensuref(sum_a == sum_b, "sum(a_i)=%d must equal sum(b_i)=%d", sum_a, sum_b);

    inf.readEof();
}
