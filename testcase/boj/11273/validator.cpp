#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int g = inf.readInt(1, 100000, "g");
    inf.readEoln();

    for (int i = 0; i < g; ++i) {
        inf.readInt(0, 10000, "goblin_x");
        inf.readSpace();
        inf.readInt(0, 10000, "goblin_y");
        inf.readEoln();
    }

    int m = inf.readInt(1, 20000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(0, 10000, "sprinkler_x");
        inf.readSpace();
        inf.readInt(0, 10000, "sprinkler_y");
        inf.readSpace();
        inf.readInt(1, 100, "r");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
