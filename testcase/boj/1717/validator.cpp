#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Read m operations
    for (int i = 0; i < m; i++) {
        int op = inf.readInt(0, 1, "op");
        inf.readSpace();
        int a = inf.readInt(0, n, "a");
        inf.readSpace();
        int b = inf.readInt(0, n, "b");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
