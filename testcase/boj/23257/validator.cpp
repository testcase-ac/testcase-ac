#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -1023, 1023, "a_i");
    for (int i = 0; i < n; ++i) {
        ensuref(abs(a[i]) < 1024, "|a_%d| must be less than 2^10, got %d",
                i + 1, a[i]);
    }
    inf.readEoln();

    inf.readEof();
}
