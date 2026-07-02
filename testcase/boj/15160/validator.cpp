#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int c = inf.readInt(1, 1000, "C");
    inf.readEoln();

    int stuckAtoms = 0;
    const string rowPattern = "[.#OA]{" + to_string(c) + "}";
    for (int i = 0; i < r; ++i) {
        string row = inf.readToken(rowPattern, "row");
        inf.readEoln();
        for (char cell : row) {
            if (cell == 'A') {
                ++stuckAtoms;
            }
        }
    }

    ensuref(stuckAtoms == 2, "expected exactly two A cells, found %d", stuckAtoms);
    inf.readEof();
}
