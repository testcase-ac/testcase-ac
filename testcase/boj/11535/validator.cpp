#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5, "n");
    inf.readSpace();

    vector<int> capacities(n);
    capacities[0] = inf.readInt(2, 64, "c_1");
    for (int i = 1; i < n; ++i) {
        inf.readSpace();
        capacities[i] = inf.readInt(1, capacities[i - 1] - 1, "c_i");
    }

    inf.readSpace();
    inf.readInt(1, capacities[0] - 1, "V");
    inf.readEoln();
    inf.readEof();

    return 0;
}
