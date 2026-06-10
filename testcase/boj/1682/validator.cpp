#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<bool> seen(9, false);
    for (int i = 1; i <= 8; ++i) {
        int value = inf.readInt(1, 8, "a_i");
        ensuref(!seen[value], "duplicate value %d at position %d", value, i);
        seen[value] = true;

        if (i < 8) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
