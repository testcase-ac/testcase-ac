#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100, "N");
        inf.readEoln();

        int side = 2 * N;
        for (int row = 1; row <= side; ++row) {
            string line = inf.readToken("[IO]{1,200}", "C_i");
            ensuref((int)line.size() == side,
                    "case %d row %d has length %d, expected %d",
                    tc, row, (int)line.size(), side);
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
