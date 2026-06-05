#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 5000, "N");
    inf.readSpace();
    int m = inf.readInt(3, 20000, "M");
    inf.readEoln();

    int j = inf.readInt(1, n, "J");
    inf.readEoln();

    int k = inf.readInt(1, n / 2, "K");
    inf.readEoln();

    vector<bool> used(n + 1, false);
    used[j] = true;

    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int a = inf.readInt(1, n, "A_i");
        ensuref(!used[a], "A-type house %d is duplicated or is J: %d", i + 1, a);
        used[a] = true;
    }
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int b = inf.readInt(1, n, "B_i");
        ensuref(!used[b], "B-type house %d is duplicated or conflicts with J/A: %d", i + 1, b);
        used[b] = true;
    }
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(1, n, "X");
        inf.readSpace();
        int y = inf.readInt(1, n, "Y");
        inf.readSpace();
        inf.readInt(1, 100, "Z");
        inf.readEoln();
    }

    inf.readEof();
}
