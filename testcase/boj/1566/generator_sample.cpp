#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MIN_A = -26;
const int MAX_A = 35;

int boundedValue(int value) {
    return max(MIN_A, min(MAX_A, value));
}

void flipRowsAndColumns(vector<vector<int>>& a) {
    int n = (int)a.size();
    int m = (int)a[0].size();

    for (int i = 0; i < n; ++i) {
        if (rnd.next(2) == 1) {
            for (int j = 0; j < m; ++j) {
                a[i][j] = -a[i][j];
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        if (rnd.next(2) == 1) {
            for (int i = 0; i < n; ++i) {
                a[i][j] = -a[i][j];
            }
        }
    }
}

vector<vector<int>> positiveBase(int n, int m) {
    vector<vector<int>> a(n, vector<int>(m));
    int low = rnd.next(1, 7);
    int high = rnd.next(low, min(MAX_A, low + rnd.next(0, 12)));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = rnd.next(low, high);
        }
    }
    return a;
}

vector<vector<int>> mixedSolvable(int n, int m) {
    vector<vector<int>> a = positiveBase(n, m);
    int tweaks = rnd.next(1, max(1, n * m / 2));

    for (int k = 0; k < tweaks; ++k) {
        int i = rnd.next(n);
        int j = rnd.next(m);
        a[i][j] = rnd.next(-26, 26);
    }

    flipRowsAndColumns(a);
    return a;
}

vector<vector<int>> zeroSumTrap(int n, int m) {
    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = rnd.next(-8, 8);
        }
    }

    if (rnd.next(2) == 0) {
        int row = rnd.next(n);
        int sum = 0;
        for (int j = 0; j + 1 < m; ++j) {
            a[row][j] = rnd.next(-8, 8);
            sum += a[row][j];
        }
        a[row][m - 1] = boundedValue(-sum);
    } else {
        int col = rnd.next(m);
        int sum = 0;
        for (int i = 0; i + 1 < n; ++i) {
            a[i][col] = rnd.next(-8, 8);
            sum += a[i][col];
        }
        a[n - 1][col] = boundedValue(-sum);
    }

    return a;
}

vector<vector<int>> sparseSigned(int n, int m) {
    vector<vector<int>> a(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int roll = rnd.next(100);
            if (roll < 45) {
                a[i][j] = 0;
            } else if (roll < 70) {
                a[i][j] = rnd.next(-3, 3);
            } else {
                a[i][j] = rnd.any(vector<int>{MIN_A, -13, 13, MAX_A});
            }
        }
    }

    return a;
}

vector<vector<int>> boundaryPattern(int n, int m) {
    vector<vector<int>> a(n, vector<int>(m));
    int shift = rnd.next(4);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int pattern = (i + j + shift) % 4;
            if (pattern == 0) {
                a[i][j] = MIN_A;
            } else if (pattern == 1) {
                a[i][j] = MAX_A;
            } else if (pattern == 2) {
                a[i][j] = rnd.next(-2, 2);
            } else {
                a[i][j] = rnd.next(-10, 10);
            }
        }
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 8);
    int m = rnd.next(1, 8);

    if (rnd.next(8) == 0) {
        n = rnd.next(9, 18);
        m = rnd.next(9, 18);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    }

    vector<vector<int>> a;
    if (mode == 0) {
        a = positiveBase(n, m);
    } else if (mode == 1) {
        a = mixedSolvable(n, m);
    } else if (mode == 2) {
        a = zeroSumTrap(n, m);
    } else if (mode == 3) {
        a = sparseSigned(n, m);
    } else {
        a = boundaryPattern(n, m);
    }

    println(n, m);
    for (const vector<int>& row : a) {
        println(row);
    }

    return 0;
}
