#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> b(5);
    for (int i = 0; i < 5; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        b[i] = inf.readInt(1, 30, format("b_%d", i + 1));
    }
    inf.readEoln();

    for (int i = 1; i < 5; ++i) {
        ensuref(b[i - 1] < b[i], "fees must be strictly increasing: b_%d=%d, b_%d=%d",
                i, b[i - 1], i + 1, b[i]);
    }

    inf.readEof();
}
