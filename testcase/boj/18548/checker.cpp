#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> perm;
vector<int> allowed;

struct Answer {
    int m;
};

bool containsPermutation(const vector<int>& values) {
    for (int start = 0; start + n <= (int)values.size(); ++start) {
        bool same = true;
        for (int i = 0; i < n; ++i) {
            if (values[start + i] != perm[i]) {
                same = false;
                break;
            }
        }
        if (same) {
            return true;
        }
    }
    return false;
}

Answer readAnswer(InStream& stream) {
    int maxM = 2 * n - 1;
    int m = stream.readInt(n, maxM, "matrix size");

    vector<vector<int>> matrix(m, vector<int>(m));
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < m; ++col) {
            int value = stream.readInt(1, n, format("matrix[%d][%d]", row + 1, col + 1).c_str());
            if (!allowed[value]) {
                stream.quitf(_wa,
                             "matrix[%d][%d]=%d is not present in the input permutation",
                             row + 1,
                             col + 1,
                             value);
            }
            matrix[row][col] = value;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after matrix");
    }

    for (int row = 0; row < m; ++row) {
        if (!containsPermutation(matrix[row])) {
            stream.quitf(_wa, "row %d does not contain the input permutation", row + 1);
        }
    }

    for (int col = 0; col < m; ++col) {
        vector<int> column(m);
        for (int row = 0; row < m; ++row) {
            column[row] = matrix[row][col];
        }
        if (!containsPermutation(column)) {
            stream.quitf(_wa, "column %d does not contain the input permutation", col + 1);
        }
    }

    return {m};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 500, "n");
    perm.resize(n);
    allowed.assign(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        perm[i] = inf.readInt(1, n, format("permutation[%d]", i + 1).c_str());
        allowed[perm[i]] = 1;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.m < jury.m) {
        quitf(_fail,
              "participant found a smaller valid matrix: jury=%d participant=%d",
              jury.m,
              participant.m);
    }
    if (participant.m > jury.m) {
        quitf(_wa,
              "matrix size is not minimum: jury=%d participant=%d",
              jury.m,
              participant.m);
    }

    quitf(_ok, "valid minimum matrix of size %d", participant.m);
}
