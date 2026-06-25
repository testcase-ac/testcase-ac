#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 200000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 199999, "b");
    inf.readSpace();
    int w = inf.readInt(1, 200000, "w");
    inf.readSpace();
    int m = inf.readInt(2, 200000, "M");
    inf.readEoln();

    ensuref(b < m, "b must be less than M: b=%d, M=%d", b, m);

    long long fixedClasses = 1LL * b * w;
    long long capacity = 1LL * m * w;
    ensuref(1LL * a + fixedClasses <= capacity,
            "schedule must be feasible: a + b*w = %lld, M*w = %lld",
            1LL * a + fixedClasses, capacity);
    ensuref(capacity <= 200000LL, "M*w must be at most 200000: %lld", capacity);

    for (int i = 0; i < a; ++i) {
        inf.readLong(1LL, 1000000000LL, "F_i");
        inf.readEoln();
    }

    for (int day = 0; day < w; ++day) {
        vector<long long> floors = inf.readLongs(b, 1LL, 1000000000LL, "S_i_j");
        (void)floors;
        inf.readEoln();
    }

    inf.readEof();
}
