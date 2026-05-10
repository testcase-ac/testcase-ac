#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly 8 notes, each in [1,8]
    vector<int> notes = inf.readInts(8, 1, 8, "note");
    inf.readEoln();

    // Check uniqueness: each of 1..8 appears exactly once
    vector<bool> seen(9, false);
    for (int i = 0; i < 8; i++) {
        int x = notes[i];
        ensuref(!seen[x], "Duplicate note %d at position %d", x, i+1);
        seen[x] = true;
    }
    for (int x = 1; x <= 8; x++) {
        ensuref(seen[x], "Missing note %d", x);
    }

    inf.readEof();
    return 0;
}
