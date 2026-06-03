#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    set<long long> brands;
    for (int i = 0; i < n; ++i) {
        long long brand = inf.readLong(1LL, 2147483647LL, "brand");
        ensuref(brands.insert(brand).second, "duplicate brand at index %d: %lld", i + 1, brand);

        bool lastOverall = i + 1 == n;
        bool lineEnd = (i + 1) % 20 == 0 || lastOverall;
        if (lineEnd) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
