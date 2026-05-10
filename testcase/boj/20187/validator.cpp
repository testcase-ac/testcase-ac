#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read k
    int k = inf.readInt(1, 8, "k");
    inf.readEoln();

    // 2. Read 2k folding instructions, each must be D/U/R/L
    int n = 2 * k;
    vector<string> folds;
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken("[A-Z]", "folding_instruction");
        ensuref(s == "D" || s == "U" || s == "R" || s == "L",
            "Invalid folding instruction at position %d: '%s' (must be D, U, R, or L)", i+1, s.c_str());
        folds.push_back(s);
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read h
    int h = inf.readInt(0, 3, "h");
    inf.readEoln();

    // 4. Global constraints: must have exactly k horizontal and k vertical folds
    int cnt_h = 0, cnt_v = 0;
    for (int i = 0; i < n; ++i) {
        if (folds[i] == "D" || folds[i] == "U") cnt_h++;
        if (folds[i] == "R" || folds[i] == "L") cnt_v++;
    }
    ensuref(cnt_h == k, "There must be exactly k=%d horizontal folds (D/U), found %d", k, cnt_h);
    ensuref(cnt_v == k, "There must be exactly k=%d vertical folds (R/L), found %d", k, cnt_v);

    inf.readEof();
}
