#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "N");
    inf.readEoln();

    vector<string> weight1(n), weight2(n);
    for (int i = 0; i < n; ++i) {
        weight1[i] = inf.readToken("[.1-9]{1,20}", "weight1_row");
        inf.readEoln();
        ensuref((int)weight1[i].size() == n,
                "weight1 row %d has length %d, expected %d",
                i, (int)weight1[i].size(), n);
    }
    for (int i = 0; i < n; ++i) {
        weight2[i] = inf.readToken("[.1-9]{1,20}", "weight2_row");
        inf.readEoln();
        ensuref((int)weight2[i].size() == n,
                "weight2 row %d has length %d, expected %d",
                i, (int)weight2[i].size(), n);
    }

    for (int i = 0; i < n; ++i) {
        ensuref(weight1[i][i] == '.', "weight1 diagonal at (%d, %d) is not '.'", i, i);
        ensuref(weight2[i][i] == '.', "weight2 diagonal at (%d, %d) is not '.'", i, i);
        for (int j = i + 1; j < n; ++j) {
            ensuref(weight1[i][j] == weight1[j][i],
                    "weight1 is not symmetric at (%d, %d): %c vs %c",
                    i, j, weight1[i][j], weight1[j][i]);
            ensuref(weight2[i][j] == weight2[j][i],
                    "weight2 is not symmetric at (%d, %d): %c vs %c",
                    i, j, weight2[i][j], weight2[j][i]);

            bool edge1 = weight1[i][j] != '.';
            bool edge2 = weight2[i][j] != '.';
            ensuref(edge1 == edge2,
                    "edge presence differs between weight matrices at (%d, %d)",
                    i, j);
        }
    }

    inf.readEof();
    return 0;
}
