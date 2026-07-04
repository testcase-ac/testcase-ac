#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<int> count(1001, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int a = inf.readInt(0, 1000, "a_i");
        ++count[a];
    }
    inf.readEoln();

    for (int value = 1; value <= 1000; ++value) {
        ensuref(count[value] == 0 || count[value] == 2,
                "nonzero value %d appears %d times, expected exactly 2 if present",
                value,
                count[value]);
    }

    inf.readEof();
}
