#include "testlib.h"

#include <cstdlib>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Rational {
    int p;
    int q;
};

static string formatRational(Rational value) {
    if (value.p == 0) {
        return "0";
    }
    if (value.q == 1) {
        return to_string(value.p);
    }
    return to_string(value.p) + "/" + to_string(value.q);
}

static vector<Rational> buildPool() {
    vector<Rational> values;
    for (int p = -9; p <= 9; ++p) {
        for (int q = 1; q <= 9; ++q) {
            if (q == 1 || gcd(abs(p), q) == 1) {
                values.push_back({p, q});
            }
        }
    }
    return values;
}

static Rational randomNonZero(const vector<Rational>& pool) {
    Rational value;
    do {
        value = rnd.any(pool);
    } while (value.p == 0);
    return value;
}

static void printMatrix(const vector<vector<Rational>>& matrix) {
    println((int)matrix.size(), (int)matrix[0].size());
    for (const auto& row : matrix) {
        for (int j = 0; j < (int)row.size(); ++j) {
            if (j) {
                cout << ' ';
            }
            cout << formatRational(row[j]);
        }
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<Rational> pool = buildPool();
    const int mode = rnd.next(0, 5);
    int n = rnd.next(1, 5);
    int m = rnd.next(1, 5);
    vector<vector<Rational>> matrix(n, vector<Rational>(m, {0, 1}));

    if (mode == 0) {
        for (auto& row : matrix) {
            for (auto& value : row) {
                value = rnd.any(pool);
            }
        }
    } else if (mode == 1) {
        double zeroProbability = rnd.next(0.45, 0.8);
        for (auto& row : matrix) {
            for (auto& value : row) {
                if (rnd.next() > zeroProbability) {
                    value = randomNonZero(pool);
                }
            }
        }
    } else if (mode == 2) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
        matrix.assign(n, vector<Rational>(m, {0, 1}));
        int diagonal = min(n, m);
        for (int i = 0; i < diagonal; ++i) {
            matrix[i][i] = {1, 1};
            for (int j = i + 1; j < m; ++j) {
                if (rnd.next(0, 2) == 0) {
                    matrix[i][j] = rnd.any(pool);
                }
            }
        }
        shuffle(matrix.begin(), matrix.end());
    } else if (mode == 3) {
        int baseRows = rnd.next(1, n);
        for (int i = 0; i < baseRows; ++i) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = rnd.any(pool);
            }
        }
        for (int i = baseRows; i < n; ++i) {
            matrix[i] = matrix[rnd.next(0, baseRows - 1)];
        }
        shuffle(matrix.begin(), matrix.end());
    } else if (mode == 4) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
        if (rnd.next(0, 1) == 0) {
            n = 1;
        } else {
            m = 1;
        }
        matrix.assign(n, vector<Rational>(m, {0, 1}));
        for (auto& row : matrix) {
            for (auto& value : row) {
                value = rnd.any(pool);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int p = rnd.next(-9, 9);
                int q = rnd.next(1, 9);
                int g = gcd(abs(p), q);
                p /= g;
                q /= g;
                matrix[i][j] = {p, q};
            }
        }
    }

    printMatrix(matrix);
    return 0;
}
