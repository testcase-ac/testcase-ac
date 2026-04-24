#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n, k, l
    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100, "k");
    inf.readSpace();
    int l = inf.readInt(1, 100, "l");
    inf.readEoln();

    // Validate k <= l as per θ = k/l and 0 < θ ≤ 1
    ensuref(k <= l,
            "Invalid ratio: k must be <= l, but k=%d, l=%d", k, l);

    // Second line: string w of length n, lowercase letters
    string w = inf.readToken("[a-z]+", "w");
    inf.readEoln();
    ensuref((int)w.length() == n,
            "Length of w must be exactly n: expected %d, got %d",
            n, (int)w.length());

    // No extra content
    inf.readEof();
    return 0;
}
