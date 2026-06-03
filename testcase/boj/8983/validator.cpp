#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_COUNT = 100000;
    const long long MAX_COORD = 1000000000LL;

    int M = inf.readInt(1, MAX_COUNT, "M");
    inf.readSpace();
    int N = inf.readInt(1, MAX_COUNT, "N");
    inf.readSpace();
    long long L = inf.readLong(1LL, MAX_COORD, "L");
    inf.readEoln();

    set<long long> shootingPositions;
    for (int i = 0; i < M; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        long long x = inf.readLong(1LL, MAX_COORD, "x_i");
        ensuref(shootingPositions.insert(x).second,
                "duplicate shooting position at index %d: %lld", i + 1, x);
    }
    inf.readEoln();

    set<pair<long long, long long>> animals;
    for (int i = 0; i < N; ++i) {
        long long a = inf.readLong(1LL, MAX_COORD, "a_j");
        inf.readSpace();
        long long b = inf.readLong(1LL, MAX_COORD, "b_j");
        inf.readEoln();

        ensuref(animals.insert({a, b}).second,
                "duplicate animal position at index %d: (%lld, %lld)",
                i + 1, a, b);
    }

    inf.readEof();
    return 0;
}
