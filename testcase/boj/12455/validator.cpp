#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 8, "N");
        inf.readSpace();
        int K = inf.readInt(1, 8, "K");
        inf.readEoln();

        for (int i = 1; i <= N; ++i) {
            int c = inf.readInt(1, K, "c_i");
            inf.readSpace();
            int t = inf.readInt(1, K, "t_i");
            inf.readSpace();
            inf.readInt(1, 1000, "s_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
