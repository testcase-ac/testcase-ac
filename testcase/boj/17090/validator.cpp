#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500, "N");
    inf.readSpace();
    int m = inf.readInt(3, 500, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLine("[URDL]{" + std::to_string(m) + "}", "maze_row");
    }

    inf.readEof();
}
