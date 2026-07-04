#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

int randomSmallValue() {
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        return rnd.next(1, 9);
    }
    if (mode == 1) {
        return rnd.any(vector<int>{1, 2, 3, 4, 6, 8, 9, 12, 16});
    }
    return rnd.next(1, 64);
}

void printMatrix(const Matrix& mat) {
    println(static_cast<int>(mat.size()), static_cast<int>(mat[0].size()));
    for (const auto& row : mat) {
        println(row);
    }
}

Matrix makeRandomMatrix(int rows, int cols, int lo, int hi) {
    Matrix mat(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] = rnd.next(lo, hi);
        }
    }
    return mat;
}

Matrix tensorProduct(const Matrix& left, const Matrix& right) {
    int p = static_cast<int>(left.size());
    int q = static_cast<int>(left[0].size());
    int n = static_cast<int>(right.size());
    int m = static_cast<int>(right[0].size());
    Matrix result(p * n, vector<int>(q * m));
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < q; ++j) {
            for (int bi = 0; bi < n; ++bi) {
                for (int bj = 0; bj < m; ++bj) {
                    result[i * n + bi][j * m + bj] = left[i][j] * right[bi][bj];
                }
            }
        }
    }
    return result;
}

Matrix makeTensorCase() {
    vector<pair<int, int>> leftDims = {{1, 2}, {2, 1}, {2, 2}, {2, 3}, {3, 2}};
    vector<pair<int, int>> rightDims = {{1, 2}, {2, 1}, {2, 2}, {3, 1}, {1, 3}, {3, 2}};
    auto [p, q] = rnd.any(leftDims);
    auto [n, m] = rnd.any(rightDims);

    Matrix left = makeRandomMatrix(p, q, 1, rnd.next(2, 12));
    Matrix right = makeRandomMatrix(n, m, 1, rnd.next(2, 24));
    return tensorProduct(left, right);
}

Matrix makeNearTensorCase() {
    Matrix mat = makeTensorCase();
    int r = static_cast<int>(mat.size());
    int c = static_cast<int>(mat[0].size());
    int i = rnd.next(0, r - 1);
    int j = rnd.next(0, c - 1);
    int delta = rnd.next(1, 7);
    if (mat[i][j] + delta <= 65536) {
        mat[i][j] += delta;
    } else {
        mat[i][j] -= delta;
    }
    return mat;
}

Matrix makeBlockyCase() {
    int blockRows = rnd.next(1, 3);
    int blockCols = rnd.next(1, 3);
    int rowBlocks = rnd.next(2, 4);
    int colBlocks = rnd.next(2, 4);
    Matrix block = makeRandomMatrix(blockRows, blockCols, 1, rnd.next(3, 18));
    Matrix scales = makeRandomMatrix(rowBlocks, colBlocks, 1, rnd.next(2, 16));
    return tensorProduct(scales, block);
}

Matrix makePrimeDimensionCase() {
    int rows = rnd.any(vector<int>{2, 3, 5, 7});
    int cols = rnd.any(vector<int>{2, 3, 5, 7});
    Matrix mat = makeRandomMatrix(rows, cols, 1, rnd.next(5, 80));
    if (rnd.next(0, 1)) {
        int common = rnd.any(vector<int>{2, 3, 4});
        for (auto& row : mat) {
            for (int& value : row) {
                value *= common;
            }
        }
    }
    return mat;
}

Matrix makeSkinnyCase() {
    int rows = rnd.next(0, 1) ? 1 : rnd.next(2, 9);
    int cols = rows == 1 ? rnd.next(2, 12) : 1;
    Matrix mat(rows, vector<int>(cols));
    int base = randomSmallValue();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int multiplier = rnd.any(vector<int>{1, 1, 2, 3, 5, 8});
            mat[i][j] = min(65536, base * multiplier + rnd.next(0, 3));
        }
    }
    return mat;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(4, 8);
    vector<Matrix> cases;
    cases.reserve(caseCount);
    for (int tc = 0; tc < caseCount; ++tc) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            cases.push_back(makeTensorCase());
        } else if (mode == 1) {
            cases.push_back(makeNearTensorCase());
        } else if (mode == 2) {
            cases.push_back(makeBlockyCase());
        } else if (mode == 3) {
            cases.push_back(makePrimeDimensionCase());
        } else {
            cases.push_back(makeSkinnyCase());
        }
    }

    shuffle(cases.begin(), cases.end());
    for (const Matrix& mat : cases) {
        printMatrix(mat);
    }
    println(0, 0);
    return 0;
}
