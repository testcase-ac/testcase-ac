#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, n, "a_i");
    inf.readEoln();

    vector<bool> seen(n + 1);
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[a[i]], "a_%d is duplicated: %d", i + 1, a[i]);
        seen[a[i]] = true;
    }

    inf.readEof();
}
