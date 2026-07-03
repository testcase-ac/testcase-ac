#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    string rowPattern = "[BW]{" + to_string(n) + "," + to_string(n) + "}";
    for (int i = 1; i <= n; ++i) {
        inf.readLine(rowPattern, "row");
    }

    inf.readEof();
}
