#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_K = 2000000000000LL;

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        long long K = inf.readLong(1LL, MAX_K, "K");
        inf.readEoln();

        for (int i = 1; i <= N; ++i) {
            inf.readLong(1LL, K, "c_i");
            inf.readSpace();
            inf.readLong(1LL, K, "t_i");
            inf.readSpace();
            inf.readInt(1, 1000, "s_i");
            inf.readEoln();
        }
    }

    inf.readEof();
}
