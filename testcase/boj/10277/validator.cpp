#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 4587520, "C");
    inf.readSpace();
    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int o = inf.readInt(1, 50000, "O");
    inf.readEoln();

    for (int i = 0; i < o; ++i) {
        string command = inf.readToken("change|groupchange|state", "command");
        inf.readSpace();

        if (command == "change") {
            inf.readInt(0, c - 1, "X");
            inf.readSpace();
            inf.readInt(-n, n, "S");
            inf.readEoln();
        } else if (command == "groupchange") {
            int a = inf.readInt(0, c - 1, "A");
            inf.readSpace();
            int b = inf.readInt(0, c - 1, "B");
            inf.readSpace();
            inf.readInt(-n, n, "S");
            inf.readEoln();

            ensuref(a <= b, "expected A <= B, found A=%d and B=%d", a, b);
        } else {
            inf.readInt(0, c - 1, "X");
            inf.readEoln();
        }
    }

    inf.readEof();
}
