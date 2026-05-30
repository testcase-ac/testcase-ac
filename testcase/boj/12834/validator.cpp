#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int V = inf.readInt(1, 1000, "V");
    inf.readSpace();
    int E = inf.readInt(0, 10000, "E");
    inf.readEoln();

    int A = inf.readInt(1, V, "A");
    inf.readSpace();
    int B = inf.readInt(1, V, "B");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        inf.readInt(1, V, "H_i");
        if (i + 1 < N) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    // CHECK: The statement does not forbid self-loops or repeated roads.
    for (int i = 0; i < E; ++i) {
        inf.readInt(1, V, "a");
        inf.readSpace();
        inf.readInt(1, V, "b");
        inf.readSpace();
        inf.readInt(1, 100, "l");
        inf.readEoln();
    }

    inf.readEof();
}
