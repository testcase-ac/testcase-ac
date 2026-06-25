#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readSpace();
    int m = inf.readInt(1, 50, "m");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "t");
    inf.readEoln();

    string rowPattern = "[RGB.]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readLine(rowPattern, "clipboard_row");
    }

    inf.readEof();
}
