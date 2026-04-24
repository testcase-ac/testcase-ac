#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of ingredients
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    vector<long long> S(N), B(N);
    __int128 totalSourness = 1;
    long long totalBitterness = 0;

    for (int i = 0; i < N; i++) {
        // Read sourness and bitterness for ingredient i
        S[i] = inf.readLong(1, 1000000000LL, "S_i");
        inf.readSpace();
        B[i] = inf.readLong(1, 1000000000LL, "B_i");
        inf.readEoln();

        // Accumulate to check global bounds
        totalSourness *= S[i];
        totalBitterness += B[i];
    }

    // The statement guarantees that if you use all ingredients,
    // both the product of sourness and the sum of bitterness
    // are positive integers strictly less than 1e9.
    ensuref(totalSourness < 1000000000LL,
            "Product of all S values must be < 1e9, but is %lld",
            (long long)totalSourness);
    ensuref(totalBitterness < 1000000000LL,
            "Sum of all B values must be < 1e9, but is %lld",
            totalBitterness);

    inf.readEof();
    return 0;
}
