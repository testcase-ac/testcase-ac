#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    long long prev = 0;
    for (int i = 0; i < N; i++) {
        long long area = inf.readLong(1LL, 2147483647LL, "area");
        inf.readEoln();
        if (i > 0) {
            ensuref(area >= prev,
                    "Catalog is not ascending at index %d: %lld < %lld",
                    i, area, prev);
        }
        prev = area;
    }

    inf.readEof();
    return 0;
}
