#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<int> degreeSequence;

struct Answer {
    bool impossible;
};

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, 1, "first output token");

    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1 sentinel");
        }
        return {true};
    }

    vector<vector<int>> matrix(n, vector<int>(n));
    matrix[0][0] = first;

    for (int col = 1; col < n; ++col) {
        matrix[0][col] = stream.readInt(0, 1, format("a[1][%d]", col + 1).c_str());
    }
    for (int row = 1; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            matrix[row][col] = stream.readInt(0, 1, format("a[%d][%d]", row + 1, col + 1).c_str());
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after adjacency matrix");
    }

    for (int row = 0; row < n; ++row) {
        if (matrix[row][row] != 0) {
            stream.quitf(_wa, "diagonal entry a[%d][%d] is %d instead of 0",
                         row + 1, row + 1, matrix[row][row]);
        }
    }

    for (int row = 0; row < n; ++row) {
        int degree = 0;
        for (int col = 0; col < n; ++col) {
            if (matrix[row][col] != matrix[col][row]) {
                stream.quitf(_wa, "matrix is not symmetric at (%d, %d): %d vs %d",
                             row + 1, col + 1, matrix[row][col], matrix[col][row]);
            }
            degree += matrix[row][col];
        }
        if (degree != degreeSequence[row]) {
            stream.quitf(_wa, "row %d has degree %d instead of %d",
                         row + 1, degree, degreeSequence[row]);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    degreeSequence.resize(n);
    for (int i = 0; i < n; ++i) {
        degreeSequence[i] = inf.readInt();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant produced a valid graph while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury provides a graph");
    }

    quitf(_ok, "participant graph has the required degree sequence");
}
