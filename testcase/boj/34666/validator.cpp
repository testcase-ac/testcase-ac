#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int grade = inf.readInt(1, 5, "grade");
        inf.readSpace();
        int language = inf.readInt(0, 60, "language");
        inf.readSpace();
        int reading = inf.readInt(0, 60, "reading");
        inf.readSpace();
        int listening = inf.readInt(0, 60, "listening");
        inf.readEoln();
    }

    inf.readEof();
}
