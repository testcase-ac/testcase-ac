#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of terms N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // To ensure no two terms have the same exponent
    set<long long> exponents;
    for (int i = 0; i < N; i++) {
        // Coefficient C: 1 ≤ C ≤ 100
        int C = inf.readInt(1, 100, "C_i");
        inf.readSpace();
        // Exponent K: 0 ≤ K ≤ 10^9
        long long K = inf.readLong(0LL, 1000000000LL, "K_i");
        inf.readEoln();

        // No duplicate exponents allowed
        ensuref(exponents.count(K) == 0,
                "Duplicate exponent detected: K = %lld at term index %d", K, i + 1);
        exponents.insert(K);
    }

    inf.readEof();
    return 0;
}
