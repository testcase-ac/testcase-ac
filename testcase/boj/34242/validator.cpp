#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the string S
    string S = inf.readToken("[^]+", "S");
    inf.readEoln();

    int n = S.size();
    ensuref(1 <= n && n <= 300000, "Length of S (%d) is out of bounds [1, 300000]", n);

    for (int i = 0; i < n; ++i) {
        ensuref(S[i] == '+' || S[i] == '-' || S[i] == '^',
            "S[%d] = '%c' is not one of '+', '-', '^'", i, S[i]);
    }

    inf.readEof();
}
