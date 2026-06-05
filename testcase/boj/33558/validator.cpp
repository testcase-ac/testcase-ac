#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200, "m");
    inf.readEoln();

    int u = inf.readInt(1, 200, "u");
    inf.readSpace();
    int v = inf.readInt(1, 200, "v");
    inf.readEoln();

    for (int i = 0; i < u; ++i) {
        string row = inf.readToken("[A-Za-z0-9]{1,200}", "texture_row");
        ensuref((int)row.size() == v, "texture row %d has length %d, expected %d",
                i + 1, (int)row.size(), v);
        inf.readEoln();
    }

    string method = inf.readToken("[a-z-]{6,15}", "method");
    ensuref(method == "clamp-to-edge" || method == "repeat" ||
                    method == "mirrored-repeat",
            "unknown wrapping method: %s", method.c_str());
    inf.readEoln();

    inf.readEof();
}
