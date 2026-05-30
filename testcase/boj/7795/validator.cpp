#include "testlib.h"
using namespace std;

void readPositiveSize(const string& name) {
    inf.readToken("[1-9][0-9]*", name.c_str());
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; cap total input size.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int N = inf.readInt(1, 20000, "N");
        inf.readSpace();
        int M = inf.readInt(1, 20000, "M");
        inf.readEoln();

        for (int i = 0; i < N; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            readPositiveSize("A_i");
        }
        inf.readEoln();

        for (int i = 0; i < M; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            readPositiveSize("B_i");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
