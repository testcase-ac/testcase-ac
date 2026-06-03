#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int length = inf.readInt(10, 1000, "length");
    inf.readEoln();

    set<int> positions;
    for (int color = 0; color < 3; ++color) {
        // CHECK: The statement says points are on tape marks but does not exclude
        // the 0 cm endpoint, so accept every integer mark from 0 through length.
        int first = inf.readInt(0, length, "position");
        inf.readSpace();
        int second = inf.readInt(0, length, "position");
        inf.readEoln();

        ensuref(positions.insert(first).second, "duplicate point position: %d", first);
        ensuref(positions.insert(second).second, "duplicate point position: %d", second);
    }

    inf.readEof();
}
