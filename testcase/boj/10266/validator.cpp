#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    // Read first clock angles
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = inf.readInt(0, 360000 - 1, "a_i");
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // Read second clock angles
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = inf.readInt(0, 360000 - 1, "b_i");
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // Check for duplicates in each clock
    const int MAX_ANGLE = 360000;
    vector<char> seen(MAX_ANGLE, 0);
    for (int i = 0; i < n; i++) {
        int v = a[i];
        ensuref(!seen[v], "Duplicate angle %d in the first clock", v);
        seen[v] = 1;
    }
    // clear seen
    for (int i = 0; i < n; i++) {
        seen[a[i]] = 0;
    }
    for (int i = 0; i < n; i++) {
        int v = b[i];
        ensuref(!seen[v], "Duplicate angle %d in the second clock", v);
        seen[v] = 1;
    }

    // Final EOF check
    inf.readEof();
    return 0;
}
