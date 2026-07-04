#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    int m;
    int k;
    vector<vector<int>> grid;
};

CaseData makeCase(int mode) {
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);

    if (mode == 0) {
        if (rnd.next(2) == 0) {
            n = 1;
            m = rnd.next(1, 12);
        } else {
            n = rnd.next(1, 12);
            m = 1;
        }
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    } else if (mode == 2) {
        n = rnd.next(3, 9);
        m = rnd.next(3, 9);
    }

    int k = rnd.next(1, max(n, m));
    vector<vector<int>> a(n, vector<int>(m, 0));

    if (mode == 0) {
        int segmentLimit = rnd.next(1, max(n, m));
        k = rnd.next(1, max(n, m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int along = max(i, j);
                a[i][j] = (along % (segmentLimit + 1) != segmentLimit);
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = 1;
            }
        }
        k = rnd.next(1, max(n, m));
    } else if (mode == 2) {
        int rowPeriod = rnd.next(2, 4);
        int colPeriod = rnd.next(2, 4);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = (i % rowPeriod != rowPeriod - 1 &&
                           j % colPeriod != colPeriod - 1);
            }
        }
    } else if (mode == 3) {
        double tileProbability = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = rnd.next() < tileProbability;
            }
        }
    } else {
        int stripeWidth = rnd.next(1, 3);
        bool horizontal = rnd.next(2) == 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int index = horizontal ? i : j;
                a[i][j] = (index / stripeWidth) % 2 == 0;
            }
        }
    }

    if (rnd.next(5) == 0) {
        k = max(n, m);
    }

    return {n, m, k, a};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 9);
    vector<CaseData> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        cases.push_back(makeCase(tc % 5));
    }
    shuffle(cases.begin(), cases.end());

    println(t);
    for (const CaseData& cur : cases) {
        println(cur.n, cur.m, cur.k);
        for (const vector<int>& row : cur.grid) {
            println(row);
        }
    }

    return 0;
}
