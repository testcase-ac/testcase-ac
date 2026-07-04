#include "testlib.h"

#include <string>

using namespace std;

int noteValue(const string& note) {
    int base = -1;
    if (note[0] == 'C') base = 0;
    if (note[0] == 'D') base = 2;
    if (note[0] == 'E') base = 4;
    if (note[0] == 'F') base = 5;
    if (note[0] == 'G') base = 7;
    if (note[0] == 'A') base = 9;
    if (note[0] == 'B') base = 11;

    int value = (note[1] - '0') * 12 + base;
    if (note.size() == 3) {
        ++value;
    }
    return value;
}

string readNote(const char* name) {
    return inf.readToken("[A-G][0-9]#?", name);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string left = readNote("left");
    inf.readSpace();
    string right = readNote("right");
    inf.readEoln();
    ensuref(noteValue(left) != noteValue(right),
            "initial notes must have interval at least 1: %s %s",
            left.c_str(), right.c_str());

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        readNote(format("note[%d]", i + 1).c_str());
    }
    inf.readEoln();

    inf.readEof();
}
