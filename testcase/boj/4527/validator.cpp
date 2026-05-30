#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int tc = 0; tc < N; ++tc) {
        setTestCase(tc + 1);

        int I = inf.readInt(1, 10, "I");
        inf.readEoln();

        for (int i = 0; i < I; ++i) {
            int S = inf.readInt(1, 1000, "S");
            inf.readSpace();
            int R = inf.readInt(1, 100, "R");
            inf.readEoln();
        }
    }

    inf.readEof();
}
