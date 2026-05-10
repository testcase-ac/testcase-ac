#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < Q; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(a, N, "b"); // ensure a <= b <= N
        inf.readSpace();
        int x = inf.readInt(1, 1000000000, "x");
        inf.readEoln();
    }

    inf.readEof();
}
