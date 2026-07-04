#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    int currentSize = 0;
    int popCount = 0;

    for (int i = 1; i <= n; ++i) {
        string command = inf.readToken("UBACI|IZBACI", format("command[%d]", i).c_str());
        if (command == "UBACI") {
            inf.readSpace();
            inf.readInt(1, 100000, format("X[%d]", i).c_str());
            inf.readEoln();
            ++currentSize;
        } else {
            inf.readEoln();
            ensuref(currentSize > 0, "IZBACI at operation %d pops from an empty sequence", i);
            --currentSize;
            ++popCount;
        }
    }

    ensuref(popCount >= 1, "input must contain at least one IZBACI command");
    inf.readEof();
}
