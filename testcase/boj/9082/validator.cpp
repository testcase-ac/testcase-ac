#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static bool hasValidMinePlacement(const string& digits, const string& cells) {
    int n = (int)digits.size();
    vector<int> fixed(n, -1);
    for (int i = 0; i < n; ++i) {
        if (cells[i] == '*') fixed[i] = 1;
    }

    vector<int> possible;
    possible.push_back(0);

    for (int i = 0; i < n; ++i) {
        vector<int> nextPossible;
        for (int mask : possible) {
            for (int mine = 0; mine <= 1; ++mine) {
                if (fixed[i] != -1 && mine != fixed[i]) continue;

                int nextMask = ((mask & 1) << 1) | mine;
                if (i > 0) {
                    int left = (mask >> 1) & 1;
                    int middle = mask & 1;
                    int right = mine;
                    if (left + middle + right != digits[i - 1] - '0') continue;
                }
                nextPossible.push_back(nextMask);
            }
        }
        possible.swap(nextPossible);
    }

    for (int mask : possible) {
        int left = (mask >> 1) & 1;
        int middle = mask & 1;
        if (left + middle == digits[n - 1] - '0') return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        string digits = inf.readToken("[0-9]{1,100}", "digits");
        inf.readEoln();
        string cells = inf.readToken("[#*]{1,100}", "cells");
        inf.readEoln();

        ensuref((int)digits.size() == n, "digits length is %d, expected %d", (int)digits.size(), n);
        ensuref((int)cells.size() == n, "cells length is %d, expected %d", (int)cells.size(), n);
        ensuref(hasValidMinePlacement(digits, cells), "no valid mine placement for test case %d", tc);
    }

    inf.readEof();
}
