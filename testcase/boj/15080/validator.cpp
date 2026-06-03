#include "testlib.h"

struct Time {
    int hour;
    int minute;
    int second;
};

Time readTime(const char* name) {
    Time t;
    t.hour = inf.readInt(0, 23, std::string(name) + "_hour");
    inf.readSpace();
    inf.readChar(':');
    inf.readSpace();
    t.minute = inf.readInt(0, 59, std::string(name) + "_minute");
    inf.readSpace();
    inf.readChar(':');
    inf.readSpace();
    t.second = inf.readInt(0, 59, std::string(name) + "_second");
    inf.readEoln();
    return t;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readTime("start");
    readTime("end");

    inf.readEof();
}
