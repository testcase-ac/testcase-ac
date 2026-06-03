#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000, "A");
    inf.readSpace();
    inf.readInt(0, 1000, "B");
    inf.readSpace();
    inf.readInt(0, 1000, "C");
    inf.readEoln();

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int club = 1; club <= n; ++club) {
        for (int member = 1; member <= 3; ++member) {
            inf.readInt(0, 100, "a");
            inf.readSpace();
            inf.readInt(0, 100, "b");
            inf.readSpace();
            inf.readInt(0, 100, "c");
            inf.readEoln();
        }
    }

    inf.readEof();
}
