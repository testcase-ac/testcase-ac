#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read r, c, k
    int r = inf.readInt(1, 100, "r");
    inf.readSpace();
    int c = inf.readInt(1, 100, "c");
    inf.readSpace();
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    // Read the initial 3x3 array A
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            int a = inf.readInt(1, 100, format("A_%d_%d", i, j).c_str());
            if (j < 3) inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
