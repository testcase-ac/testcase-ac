#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int day = 1; day <= n; ++day) {
        int m = inf.readInt(1, 9, "m_i");
        int previous = 0;
        for (int j = 1; j <= m; ++j) {
            inf.readSpace();
            int a = inf.readInt(1, 9, "a_i_j");
            ensuref(previous < a,
                    "day %d rice-cake types must be strictly increasing: %d then %d",
                    day, previous, a);
            previous = a;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
