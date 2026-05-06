#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read N distinct natural numbers (1 to 10000)
    vector<int> a = inf.readInts(N, 1, 10000, "a");
    inf.readEoln();

    // Check that all N numbers are distinct
    vector<int> b = a;
    sort(b.begin(), b.end());
    for (int i = 1; i < N; i++) {
        ensuref(b[i] != b[i-1],
                "Duplicate numbers found: %d appears more than once", b[i]);
    }

    inf.readEof();
    return 0;
}
