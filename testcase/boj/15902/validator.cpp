#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read L
    int L = inf.readInt(1, 3000, "L");
    inf.readEoln();

    // 2. Read n
    int n = inf.readInt(1, L, "n");
    inf.readEoln();

    // 3. Read a_1 ... a_n
    vector<int> a = inf.readInts(n, 1, 2, "a_i");
    inf.readEoln();

    // 4. Ensure sum of a_i == L
    long long sum_a = accumulate(a.begin(), a.end(), 0LL);
    ensuref(sum_a == L, "Sum of a_i (%lld) != L (%d)", sum_a, L);

    // 5. Read m
    int m = inf.readInt(1, L, "m");
    inf.readEoln();

    // 6. Read b_1 ... b_m
    vector<int> b = inf.readInts(m, 1, 2, "b_i");
    inf.readEoln();

    // 7. Ensure sum of b_i == L
    long long sum_b = accumulate(b.begin(), b.end(), 0LL);
    ensuref(sum_b == L, "Sum of b_i (%lld) != L (%d)", sum_b, L);

    inf.readEof();
}
