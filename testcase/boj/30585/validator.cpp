#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 100, "h");
    inf.readSpace();
    int w = inf.readInt(1, 100, "w");
    inf.readEoln();

    string pattern = "[01]{" + to_string(w) + "}";
    for (int row = 1; row <= h; ++row) {
        inf.readLine(pattern, "row");
    }

    inf.readEof();
}
