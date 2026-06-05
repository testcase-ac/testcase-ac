#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readSpace();
    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    vector<int> c(n);
    bool hasZeroRequiredExperience = false;
    for (int i = 0; i < n; ++i) {
        c[i] = inf.readInt(0, 1000000, "c_i");
        inf.readSpace();
        int e = inf.readInt(0, 1000000, "e_i");
        (void)e;
        inf.readEoln();

        if (c[i] == 0) {
            hasZeroRequiredExperience = true;
        }
    }
    ensuref(hasZeroRequiredExperience, "at least one hunting ground must have c_i = 0");

    vector<vector<int>> travel(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int low = (i == j ? 0 : 1);
            int high = (i == j ? 0 : 1000);
            travel[i][j] = inf.readInt(low, high, "t_i_j");
        }
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(travel[i][j] == travel[j][i],
                    "travel matrix must be symmetric at (%d, %d): %d != %d",
                    i + 1,
                    j + 1,
                    travel[i][j],
                    travel[j][i]);
        }
    }

    inf.readEof();
}
