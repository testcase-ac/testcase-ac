#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    // M must satisfy 0 ≤ M < N
    int M = inf.readInt(0, N-1, "M");
    inf.readEoln();
    // Read the M sticky‐trap descriptions
    vector<int> xs;
    xs.reserve(M);
    for (int i = 0; i < M; i++) {
        int c = inf.readInt(0, 1, "c_i");
        inf.readSpace();
        int x = inf.readInt(1, N-1, "x_i");
        inf.readSpace();
        int h = inf.readInt(-1000000, 1000000, "h_i");
        inf.readEoln();
        xs.push_back(x);
    }
    // Check all x_i are distinct
    sort(xs.begin(), xs.end());
    for (int i = 1; i < (int)xs.size(); i++) {
        ensuref(xs[i] != xs[i-1],
                "Duplicate x-coordinate detected: %d", xs[i]);
    }
    inf.readEof();
    return 0;
}
