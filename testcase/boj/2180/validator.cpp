#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // 2. For each fire, read a and b
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(0, 40000, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, 40000, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
