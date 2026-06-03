#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 1000, "L");
    inf.readEoln();

    std::string commands = inf.readToken("[EWSN]{1,1000}", "commands");
    ensuref((int)commands.size() == l, "commands length is %d, expected %d",
            (int)commands.size(), l);
    inf.readEoln();

    inf.readEof();
}
