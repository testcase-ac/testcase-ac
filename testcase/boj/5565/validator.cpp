#include "testlib.h"
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read total price of 10 books.
    // Each book's price is a positive integer <= 10000,
    // so the total must be between 10 and 100000 inclusive.
    long long total = inf.readLong(10LL, 100000LL, "total");
    inf.readEoln();

    // Read the 9 known book prices.
    // Each price must be between 1 and 10000 inclusive.
    __int128 sum_known = 0;
    for (int i = 1; i <= 9; i++) {
        long long p = inf.readLong(1LL, 10000LL, "known_price");
        inf.readEoln();
        sum_known += p;
    }

    // The missing price = total - sum_known must be a positive integer <= 10000.
    long long missing = (long long)(total - sum_known);
    ensuref(missing >= 1 && missing <= 10000,
            "Calculated missing price = %lld not in valid range [1,10000] "
            "(total=%lld, sum_known=%lld)",
            missing, total, (long long)sum_known);

    inf.readEof();
    return 0;
}
