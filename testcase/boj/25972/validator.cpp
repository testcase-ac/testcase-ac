#include "testlib.h"

#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    set<long long> positions;
    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "l_i");
        inf.readEoln();

        ensuref(positions.insert(a).second,
                "duplicate x-coordinate at domino %d: %lld", i, a);
    }

    inf.readEof();
}
