#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readEoln();

    std::string command = inf.readToken("[LRUD]{1,300000}", "command");
    ensuref(command.size() == static_cast<size_t>(n),
            "command length is %d, expected %d",
            static_cast<int>(command.size()),
            n);
    inf.readEoln();

    int q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int x = inf.readInt(-300000, 300000, "x");
        inf.readSpace();
        int y = inf.readInt(-300000, 300000, "y");
        inf.readEoln();

        ensuref(x != 0 || y != 0,
                "query %d starts at the wall coordinate (0, 0)",
                i);
    }

    inf.readEof();
    return 0;
}
