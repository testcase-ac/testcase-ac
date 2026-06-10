#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[a[i]], "duplicate value at index %d: %d", i + 1, a[i]);
        seen[a[i]] = true;
    }

    inf.readEof();
}
