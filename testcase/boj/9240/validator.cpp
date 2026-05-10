#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of arrows C
    int C = inf.readInt(2, 100000, "C");
    inf.readEoln();

    // Read C points
    for (int i = 0; i < C; i++) {
        int x = inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000, 1000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
