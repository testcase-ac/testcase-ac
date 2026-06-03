#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    for (int i = 1; i <= 10; ++i) {
        inf.readInt(1, 3, "t_i");
        inf.readEoln();
    }

    inf.readEof();
}
