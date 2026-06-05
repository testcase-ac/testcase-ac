#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    bool hasStartPlank = false;
    for (int i = 0; i < n; ++i) {
        long long l = inf.readLong(0LL, 1000000000LL, "L");
        inf.readSpace();
        long long r = inf.readLong(0LL, 1000000000LL, "R");
        inf.readEoln();

        ensuref(l < r, "plank %d has L >= R: %lld %lld", i + 1, l, r);
        if (l == 0) {
            hasStartPlank = true;
        }
    }

    ensuref(hasStartPlank, "at least one plank must start at 0");

    inf.readEof();
    return 0;
}
