#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int ni = inf.readInt(1, 1000, "ni");
    inf.readSpace();
    int mj = inf.readInt(1, 1000, "mj");
    inf.readEoln();

    string rowPattern = "[a-z]{" + to_string(mj) + "," + to_string(mj) + "}";
    for (int i = 0; i < ni; ++i) {
        inf.readLine(rowPattern, "row");
    }

    inf.readEof();
}
