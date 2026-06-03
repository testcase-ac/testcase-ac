#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

using Matrix = vector<vector<int>>;

const int MIN_A = -1000000;
const int MAX_A = 1000000;

Matrix makeOrdered(int n, int m) {
    vector<int> row(n), col(m);
    row[0] = rnd.next(-20, 20);
    col[0] = rnd.next(-20, 20);
    for (int i = 1; i < n; ++i) row[i] = row[i - 1] + rnd.next(-6, 6);
    for (int j = 1; j < m; ++j) col[j] = col[j - 1] + rnd.next(-6, 6);

    int slope = rnd.next(0, 6);
    Matrix a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = row[i] + col[j] - slope * i * j;
        }
    }
    return a;
}

Matrix makeRandom(int n, int m, int lo, int hi) {
    Matrix a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = rnd.next(lo, hi);
        }
    }
    return a;
}

void plantViolation(Matrix& a) {
    int n = int(a.size());
    int m = int(a[0].size());
    if (n < 2 || m < 2) return;

    int r1 = rnd.next(0, n - 2);
    int r2 = rnd.next(r1 + 1, n - 1);
    int c1 = rnd.next(0, m - 2);
    int c2 = rnd.next(c1 + 1, m - 1);
    int need = a[r1][c2] + a[r2][c1] - a[r1][c1] + rnd.next(1, 30);
    a[r2][c2] = min(MAX_A, max(MIN_A, need));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 7);
        int m = rnd.next(1, 7);
        if (mode == 2) n = 1;
        if (mode == 3) m = 1;
        if (mode == 4 || mode == 5) {
            n = rnd.next(2, 7);
            m = rnd.next(2, 7);
        }

        Matrix a;
        if (mode == 0 || mode == 2 || mode == 3) {
            a = makeOrdered(n, m);
        } else if (mode == 1) {
            a = makeRandom(n, m, -25, 25);
        } else if (mode == 4) {
            a = makeOrdered(n, m);
            plantViolation(a);
        } else {
            a = makeRandom(n, m, -1000000, 1000000);
        }

        println(n, m);
        for (int i = 0; i < n; ++i) {
            println(a[i]);
        }
    }

    return 0;
}
