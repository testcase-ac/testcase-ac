#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    vector<char> seen(1000001, false);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }

        int a = inf.readInt(1, 1000000, "a_i");
        ensuref(!seen[a], "a_i values must be distinct, duplicate value %d at index %d", a, i + 1);
        seen[a] = true;
    }
    inf.readEoln();

    inf.readEof();
}
