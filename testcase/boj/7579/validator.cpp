#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000000, "M");
    inf.readEoln();

    // Second line: m_i array
    vector<long long> m = inf.readLongs(N, 1LL, 10000000LL, "m_i");
    inf.readEoln();

    // Third line: c_i array
    vector<int> c = inf.readInts(N, 0, 100, "c_i");
    inf.readEoln();

    // Global constraint: sum of m_i must be at least M
    long long sum_m = 0;
    for (int i = 0; i < N; i++) {
        sum_m += m[i];
        // sum_m won't overflow long long: at most 100 * 1e7 = 1e9
    }
    ensuref(sum_m >= M,
            "Total memory provided by m_i is %lld, which is less than required M = %d",
            sum_m, M);

    inf.readEof();
    return 0;
}
