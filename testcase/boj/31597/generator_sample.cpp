#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

Matrix constantMatrix(int n) {
    return Matrix(n, vector<int>(n, rnd.next(1, n)));
}

Matrix latinMatrix(int n) {
    Matrix a(n, vector<int>(n));
    int rowShift = rnd.next(0, n - 1);
    int colShift = rnd.next(0, n - 1);
    int mul = 1;
    vector<int> coprime;
    for (int x = 1; x <= n; ++x) {
        if (gcd(x, n) == 1) {
            coprime.push_back(x);
        }
    }
    mul = rnd.any(coprime);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = ((i * mul + j + rowShift + colShift) % n) + 1;
        }
    }
    return a;
}

Matrix lowAlphabetMatrix(int n) {
    Matrix a(n, vector<int>(n));
    int hi = rnd.next(1, max(1, n / 2));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = rnd.next(1, hi);
        }
    }
    return a;
}

Matrix randomMatrix(int n) {
    Matrix a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = rnd.next(1, n);
        }
    }
    return a;
}

Matrix rowDuplicateColumnLatin(int n) {
    Matrix a = latinMatrix(n);
    int rows = rnd.next(1, n);
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    for (int idx = 0; idx < rows; ++idx) {
        int r = order[idx];
        int c1 = rnd.next(0, n - 1);
        int c2 = rnd.next(0, n - 1);
        while (c2 == c1) {
            c2 = rnd.next(0, n - 1);
        }
        a[r][c2] = a[r][c1];
    }
    return a;
}

Matrix columnDuplicateRowLatin(int n) {
    Matrix a = latinMatrix(n);
    int cols = rnd.next(1, n);
    vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    for (int idx = 0; idx < cols; ++idx) {
        int c = order[idx];
        int r1 = rnd.next(0, n - 1);
        int r2 = rnd.next(0, n - 1);
        while (r2 == r1) {
            r2 = rnd.next(0, n - 1);
        }
        a[r2][c] = a[r1][c];
    }
    return a;
}

Matrix perturbedLatin(int n) {
    Matrix a = latinMatrix(n);
    int edits = rnd.next(1, max(1, n));
    for (int k = 0; k < edits; ++k) {
        int r = rnd.next(0, n - 1);
        int c = rnd.next(0, n - 1);
        a[r][c] = rnd.next(1, n);
    }
    return a;
}

Matrix makeCase(int n, int mode) {
    if (mode == 0) {
        return latinMatrix(n);
    }
    if (mode == 1) {
        return constantMatrix(n);
    }
    if (mode == 2) {
        return rowDuplicateColumnLatin(n);
    }
    if (mode == 3) {
        return columnDuplicateRowLatin(n);
    }
    if (mode == 4) {
        return perturbedLatin(n);
    }
    if (mode == 5) {
        return lowAlphabetMatrix(n);
    }
    return randomMatrix(n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int budget = rnd.next(120, 420);
    vector<Matrix> tests;
    vector<int> required = {3, 4, rnd.next(5, 10)};

    for (int n : required) {
        int mode = rnd.next(0, 6);
        tests.push_back(makeCase(n, mode));
        budget -= n * n;
    }

    while (budget >= 9 && static_cast<int>(tests.size()) < 18) {
        int maxN = min(12, static_cast<int>(sqrt(budget)));
        int n = rnd.next(3, maxN);
        int mode = rnd.next(0, 6);
        tests.push_back(makeCase(n, mode));
        budget -= n * n;
    }

    println(static_cast<int>(tests.size()));
    for (const Matrix& a : tests) {
        println(static_cast<int>(a.size()));
        for (const vector<int>& row : a) {
            println(row);
        }
    }

    return 0;
}
