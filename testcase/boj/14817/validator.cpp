#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        int N = inf.readInt(2, 1000, "N");
        inf.readSpace();
        int C = inf.readInt(2, 2, "C");
        inf.readSpace();
        int M = inf.readInt(1, 1000, "M");
        inf.readEoln();

        for (int i = 1; i <= M; i++) {
            int P = inf.readInt(1, N, "P_i");
            inf.readSpace();
            int B = inf.readInt(1, C, "B_i");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
