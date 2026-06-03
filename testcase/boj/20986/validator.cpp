#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 5000, "N");
    inf.readEoln();

    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int h = inf.readInt(1, n, "H_i");
        ensuref(!seen[h], "H_i values must be distinct, duplicate value %d at index %d", h, i);
        seen[h] = 1;
    }
    inf.readEoln();

    inf.readEof();
}
