#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K, N, M
    int K = inf.readInt(1, 200, "K");
    inf.readSpace();
    int N = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read M edges
    for (int i = 1; i <= M; i++) {
        char buf[20];

        snprintf(buf, sizeof(buf), "A_%d", i);
        int a = inf.readInt(1, N, buf);
        inf.readSpace();

        snprintf(buf, sizeof(buf), "B_%d", i);
        int b = inf.readInt(1, N, buf);
        inf.readSpace();

        snprintf(buf, sizeof(buf), "t_%d", i);
        int t = inf.readInt(1, 100000, buf);
        inf.readSpace();

        snprintf(buf, sizeof(buf), "h_%d", i);
        int h = inf.readInt(0, 200, buf);
        inf.readEoln();

        ensuref(a != b,
                "Edge %d is a self-loop: (%d, %d)", i, a, b);
    }

    // Read start and end
    int A = inf.readInt(1, N, "start");
    inf.readSpace();
    int B = inf.readInt(1, N, "end");
    inf.readEoln();
    ensuref(A != B,
            "Start and end must be different: (%d, %d)", A, B);

    inf.readEof();
    return 0;
}
