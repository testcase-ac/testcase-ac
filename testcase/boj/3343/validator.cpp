#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read inputs with exact spacing and newline
    long long N = inf.readLong(1, 1000000000000000LL, "N");
    inf.readSpace();
    int A = inf.readInt(1, 100000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 100000, "C");
    inf.readSpace();
    int D = inf.readInt(1, 100000, "D");
    inf.readEoln();

    // Compute the minimal cost to buy at least N roses
    // We consider mixing bundles from both shops
    __int128 best = (__int128)1 << 62;  // a large initial value

    // Try i bundles from shop 1 (size A for cost B), fill rest with shop 2
    for (int i = 0; i <= C; ++i) {
        __int128 roses1 = (__int128)i * A;
        __int128 rem = N - roses1;
        if (rem < 0) rem = 0;
        __int128 y = (rem + (C - 1)) / C;  // bundles from shop 2
        __int128 cost = (__int128)i * B + y * D;
        if (cost < best) best = cost;
    }

    // Try j bundles from shop 2 (size C for cost D), fill rest with shop 1
    for (int j = 0; j <= A; ++j) {
        __int128 roses2 = (__int128)j * C;
        __int128 rem = N - roses2;
        if (rem < 0) rem = 0;
        __int128 x = (rem + (A - 1)) / A;  // bundles from shop 1
        __int128 cost = (__int128)j * D + x * B;
        if (cost < best) best = cost;
    }

    // Validate the implied global bound: answer never exceeds 1e18
    __int128 LIMIT = (__int128)1000000000000000000LL;
    ensuref(best <= LIMIT, "Minimum cost %lld exceeds 1e18", (long long)best);

    inf.readEof();
    return 0;
}
