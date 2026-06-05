#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static void printCase(const vector<int>& rows, const vector<int>& cols) {
    println((int)rows.size());
    println(rows);
    println(cols);
}

static vector<vector<int>> makeRandomMatrix(int n) {
    vector<vector<int>> a(n, vector<int>(n, 0));
    int mode = rnd.next(4);
    if (mode == 0) {
        double density = rnd.next(0.0, 1.0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = rnd.next() < density;
    } else if (mode == 1) {
        int ones = rnd.next(0, n * n);
        vector<int> cells(n * n);
        for (int i = 0; i < n * n; ++i) cells[i] = i;
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < ones; ++i) a[cells[i] / n][cells[i] % n] = 1;
    } else if (mode == 2) {
        int band = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i)
            for (int offset = 0; offset <= band; ++offset)
                a[i][(i + offset) % n] = 1;
    } else {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = (rnd.next(3) == 0) || (i == j && rnd.next(2));
    }
    return a;
}

static void printMatrixDegrees(int n) {
    vector<vector<int>> a = makeRandomMatrix(n);
    vector<int> rows(n, 0), cols(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rows[i] += a[i][j];
            cols[j] += a[i][j];
        }
    }
    if (rnd.next(2)) {
        shuffle(rows.begin(), rows.end());
        shuffle(cols.begin(), cols.end());
    }
    printCase(rows, cols);
}

static void printMismatchedSums(int n) {
    vector<int> rows(n), cols(n);
    int rowSum = 0, colSum = 0;
    for (int i = 0; i < n; ++i) {
        rows[i] = rnd.next(0, n);
        cols[i] = rnd.next(0, n);
        rowSum += rows[i];
        colSum += cols[i];
    }
    if (rowSum == colSum) {
        int idx = rnd.next(n);
        if (cols[idx] < n) ++cols[idx];
        else --cols[idx];
    }
    printCase(rows, cols);
}

static void printImpossibleEqualSum(int n) {
    vector<int> rows(n, 0), cols(n, 0);
    rows[0] = n;
    cols[0] = n;

    shuffle(rows.begin(), rows.end());
    shuffle(cols.begin(), cols.end());
    printCase(rows, cols);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 12);

    if (mode == 0) {
        printCase(vector<int>(n, 0), vector<int>(n, 0));
    } else if (mode == 1) {
        printCase(vector<int>(n, n), vector<int>(n, n));
    } else if (mode <= 3) {
        printMatrixDegrees(n);
    } else if (mode == 4) {
        printMismatchedSums(n);
    } else {
        if (n == 1) n = 2;
        printImpossibleEqualSum(n);
    }

    return 0;
}
