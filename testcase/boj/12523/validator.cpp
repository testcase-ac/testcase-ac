#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 10, "N");
        inf.readEoln();

        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                inf.readSpace();
            }

            int f = inf.readInt(1, n, "F_i");
            ensuref(f != i, "monk %d immediately follows himself", i);
        }
        inf.readEoln();
    }

    inf.readEof();
}
