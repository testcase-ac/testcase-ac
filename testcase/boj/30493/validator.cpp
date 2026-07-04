#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readEoln();

    long long previousEnd = -1;
    for (int i = 1; i <= n; ++i) {
        long long s = inf.readLong(0LL, 1000000000LL, "s_i");
        inf.readSpace();
        long long p = inf.readLong(0LL, 1000000000LL, "p_i");
        inf.readSpace();
        long long e = inf.readLong(0LL, 1000000000LL, "e_i");
        inf.readSpace();
        long long a = inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readEoln();

        ensuref(s < p, "exam %d must satisfy s_i < p_i, got %lld >= %lld", i, s, p);
        ensuref(p <= e, "exam %d must satisfy p_i <= e_i, got %lld > %lld", i, p, e);
        if (i > 1) {
            ensuref(previousEnd <= s,
                    "exams must not overlap: e_%d = %lld > s_%d = %lld",
                    i - 1, previousEnd, i, s);
        }
        previousEnd = e;
    }

    inf.readEof();
    return 0;
}
