#include "testlib.h"

#include <vector>

using namespace std;

vector<vector<int>> makeHomogeneous(int n) {
    vector<int> row(n), col(n);
    for (int i = 0; i < n; ++i) row[i] = rnd.next(-50, 50);
    for (int j = 0; j < n; ++j) col[j] = rnd.next(-50, 50);

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = row[i] + col[j];
    return a;
}

vector<vector<int>> makeStructuredMiss(int n) {
    vector<vector<int>> a = makeHomogeneous(n);
    int row = rnd.next(n);
    int col = rnd.next(n);
    int delta = rnd.next(1, 20);
    if (rnd.next(2) == 0) delta = -delta;
    a[row][col] += delta;
    return a;
}

vector<vector<int>> makeRandomMatrix(int n) {
    int lo = rnd.next(-20, 0);
    int hi = rnd.next(0, 20);
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = rnd.next(lo, hi);
    return a;
}

void printCase(const vector<vector<int>>& a) {
    println((int)a.size());
    for (const auto& row : a) println(row);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(3, 7);
    for (int tc = 0; tc < testCases; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 8);
        }

        int mode = rnd.next(100);
        if (n == 1 || mode < 40) {
            printCase(makeHomogeneous(n));
        } else if (mode < 75) {
            printCase(makeStructuredMiss(n));
        } else {
            printCase(makeRandomMatrix(n));
        }
    }

    println(0);
    return 0;
}
