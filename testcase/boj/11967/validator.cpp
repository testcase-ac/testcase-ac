#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20000, "M");
    inf.readEoln();

    for (int i = 0; i < M; ++i) {
        int x = inf.readInt(1, N, "x");
        inf.readSpace();
        int y = inf.readInt(1, N, "y");
        inf.readSpace();
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();
    }

    inf.readEof();
}
