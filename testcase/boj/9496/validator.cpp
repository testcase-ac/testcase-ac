#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    string grades = inf.readToken("[1-3]{1,50}", "G");
    ensuref((int)grades.size() == n, "grade string length is %d, expected %d",
            (int)grades.size(), n);
    inf.readEoln();

    vector<string> dislikes(n);
    for (int i = 0; i < n; ++i) {
        dislikes[i] = inf.readToken("[YN]{1,50}", "relation_row");
        ensuref((int)dislikes[i].size() == n,
                "relation row %d length is %d, expected %d", i + 1,
                (int)dislikes[i].size(), n);
        ensuref(dislikes[i][i] == 'N',
                "student %d cannot dislike themself", i + 1);
        inf.readEoln();
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(dislikes[i][j] == dislikes[j][i],
                    "relation matrix is not symmetric at (%d, %d)", i + 1,
                    j + 1);
            ensuref(grades[i] != grades[j] || dislikes[i][j] == 'N',
                    "same-grade students %d and %d cannot dislike each other",
                    i + 1, j + 1);
        }
    }

    inf.readEof();
}
