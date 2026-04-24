#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of lectures L and number of teachers T
    int L = inf.readInt(1, 5000, "L");
    inf.readSpace();
    // T must satisfy ceil(L/3) <= T <= L to guarantee enough capacity
    int minT = (L + 2) / 3;
    int T = inf.readInt(minT, L, "T");
    inf.readEoln();

    // Validate each teacher's costs
    for (int i = 0; i < T; i++) {
        int a1 = inf.readInt(1, 100000, "a_i1");
        inf.readSpace();
        int a2 = inf.readInt(1, 100000, "a_i2");
        inf.readSpace();
        int a3 = inf.readInt(1, 100000, "a_i3");
        inf.readEoln();

        ensuref(a1 < a2,
                "For teacher %d: a_i1 >= a_i2 (%d >= %d)", i, a1, a2);
        ensuref(a2 < a3,
                "For teacher %d: a_i2 >= a_i3 (%d >= %d)", i, a2, a3);
    }

    // Verify the assumption: total maximum lectures capacity >= L
    // (Each teacher can teach up to 3 lectures.)
    ensuref(3LL * T >= L,
            "Not enough total capacity: 3 * T = %lld < L = %d",
            3LL * T, L);

    inf.readEof();
    return 0;
}
