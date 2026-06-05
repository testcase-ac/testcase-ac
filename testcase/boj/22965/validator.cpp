#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<int> seen(200001, 0);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        int value = inf.readInt(1, 200000, "A_i");
        ensuref(!seen[value], "A_i values must be distinct; duplicate value %d at index %d", value, i + 1);
        seen[value] = 1;
    }
    inf.readEoln();

    inf.readEof();
}
