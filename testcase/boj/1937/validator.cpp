#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid size n
    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    // Read the bamboo forest grid: n lines each with n integers in [1, 1e6]
    for (int i = 0; i < n; i++) {
        inf.readInts(n, 1, 1000000, "bamboo");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
