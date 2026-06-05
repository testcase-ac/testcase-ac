#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[a[i]], "value %d appears more than once in the permutation", a[i]);
        seen[a[i]] = true;
    }

    inf.readEof();
}
