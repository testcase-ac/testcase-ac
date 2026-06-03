#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    inf.readInt(1, 2, "D");
    inf.readEoln();

    string rowPattern = "[dbqp]{" + to_string(n) + "," + to_string(n) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "grid_row");
        inf.readEoln();
    }

    inf.readEof();
}
