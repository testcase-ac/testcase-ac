#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct CaseData {
    int m;
    int n;
    int p;
    vector<vector<int>> s;
};

int stepValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

CaseData makeCase(int mode) {
    CaseData tc;

    if (mode == 0) {
        tc.m = 2;
        tc.n = rnd.next(1, 5);
    } else if (mode == 1) {
        tc.m = rnd.next(3, 8);
        tc.n = rnd.next(1, 8);
    } else if (mode == 2) {
        tc.m = rnd.next(2, 12);
        tc.n = 31;
    } else if (mode == 3) {
        tc.m = 1000;
        tc.n = rnd.next(1, 2);
    } else {
        tc.m = rnd.next(2, 20);
        tc.n = rnd.next(1, 12);
    }

    tc.p = rnd.next(1, tc.m);
    tc.s.assign(tc.m, vector<int>(tc.n));

    vector<int> dayMax(tc.n);
    for (int j = 0; j < tc.n; ++j) {
        if (mode == 4 && rnd.next(3) == 0) {
            dayMax[j] = rnd.any(vector<int>{1, 60000});
        } else {
            dayMax[j] = stepValue(1, 60000);
        }
    }

    for (int i = 0; i < tc.m; ++i) {
        for (int j = 0; j < tc.n; ++j) {
            int pattern = rnd.next(0, 5);
            if (i + 1 == tc.p) {
                if (pattern == 0) {
                    tc.s[i][j] = dayMax[j];
                } else if (pattern <= 3) {
                    tc.s[i][j] = stepValue(1, dayMax[j]);
                } else {
                    tc.s[i][j] = max(1, dayMax[j] - rnd.next(0, min(2000, dayMax[j] - 1)));
                }
            } else if (pattern == 0) {
                tc.s[i][j] = dayMax[j];
            } else if (pattern == 1) {
                tc.s[i][j] = stepValue(1, dayMax[j]);
            } else if (pattern == 2) {
                tc.s[i][j] = max(1, dayMax[j] - rnd.next(0, min(50, dayMax[j] - 1)));
            } else {
                tc.s[i][j] = stepValue(1, 60000);
                dayMax[j] = max(dayMax[j], tc.s[i][j]);
            }
        }
    }

    for (int j = 0; j < tc.n; ++j) {
        int forced = rnd.next(tc.m);
        tc.s[forced][j] = dayMax[j];
    }

    if (mode == 4) {
        for (int j = 0; j < tc.n; ++j) {
            if (rnd.next(4) == 0) tc.s[tc.p - 1][j] = 1;
            if (rnd.next(4) == 0) tc.s[rnd.next(tc.m)][j] = 60000;
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int caseId = 0; caseId < t; ++caseId) {
        int mode = caseId < 5 ? caseId : rnd.next(0, 4);
        CaseData tc = makeCase(mode);

        println(tc.m, tc.n, tc.p);
        for (int i = 0; i < tc.m; ++i) {
            println(tc.s[i]);
        }
    }

    return 0;
}
