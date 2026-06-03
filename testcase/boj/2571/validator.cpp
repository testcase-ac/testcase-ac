#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 90, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, 90, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
