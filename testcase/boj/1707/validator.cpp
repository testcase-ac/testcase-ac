#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int K = inf.readInt(2, 5, "K");
    inf.readEoln();

    for (int tc = 1; tc <= K; ++tc) {
        setTestCase(tc);

        int V = inf.readInt(1, 20000, "V");
        inf.readSpace();
        int E = inf.readInt(1, 200000, "E");
        inf.readEoln();

        for (int i = 1; i <= E; ++i) {
            int u = inf.readInt(1, V, "u");
            inf.readSpace();
            int v = inf.readInt(1, V, "v");
            inf.readEoln();

            ensuref(u != v, "self-loop at edge %d: (%d, %d)", i, u, v);
        }
    }

    inf.readEof();
    return 0;
}
