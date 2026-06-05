#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string side = inf.readToken("L|R", "side");
        inf.readSpace();
        string chirps = inf.readToken("[01]{1,2000}", "chirps");
        ensuref(static_cast<int>(chirps.size()) == m,
                "bird %d chirp string length is %d, expected %d",
                i + 1,
                static_cast<int>(chirps.size()),
                m);
        inf.readEoln();
    }

    inf.readEof();
}
