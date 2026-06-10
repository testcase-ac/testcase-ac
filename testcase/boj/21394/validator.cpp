#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = 0;
        for (int i = 1; i <= 9; ++i) {
            if (i > 1) {
                inf.readSpace();
            }
            int x = inf.readInt(0, 1000, "x_i");
            n += x;
        }
        inf.readEoln();

        ensuref(2 <= n && n <= 1000,
                "case %d has total card count %d, expected 2..1000",
                tc, n);
    }

    inf.readEof();
    return 0;
}
