#include "testlib.h"

#include <array>

using namespace std;

array<int, 5> readPermutation(const char* name) {
    array<int, 5> values{};
    bool seen[6] = {};

    for (int i = 0; i < 5; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        values[i] = inf.readInt(1, 5, name);
        ensuref(!seen[values[i]], "%s is not a permutation of 1..5", name);
        seen[values[i]] = true;
    }
    inf.readEoln();

    return values;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        readPermutation("f_i");
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int query = 1; query <= q; ++query) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();

        ensuref(a <= u && u <= b, "query %d must satisfy a <= u <= b", query);

        bool seen[6] = {};
        for (int i = 0; i < 5; ++i) {
            int y = inf.readInt(1, 5, "y_i");
            ensuref(!seen[y], "query %d y_i is not a permutation of 1..5", query);
            seen[y] = true;

            if (i + 1 < 5) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
