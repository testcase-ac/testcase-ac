#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    vector<bool> seen(1000001, false);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(1, 1000000, "a_i");
        ensuref(!seen[value], "duplicate a_i value at index %d: %d", i + 1, value);
        seen[value] = true;
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
