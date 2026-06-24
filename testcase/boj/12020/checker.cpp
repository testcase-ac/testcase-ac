#include "testlib.h"

#include <cmath>
#include <string>
#include <vector>

using namespace std;

const double ZERO_EPS = 1e-7;
const double ENTRY_EPS = 1e-2;
const double PRODUCT_EPS = 5e-2;

int n;
vector<vector<double>> a;

struct Answer {
    bool impossible;
    vector<vector<double>> l;
    vector<vector<double>> u;
};

double readMatrixValue(InStream& stream, const string& firstToken, bool useFirstToken,
                       const char* matrixName, int row, int col) {
    string token = useFirstToken
                       ? firstToken
                       : stream.readToken();
    try {
        size_t parsed = 0;
        double value = stod(token, &parsed);
        if (parsed != token.size() || !isfinite(value)) {
            stream.quitf(_wa, "%s[%d][%d] is not a finite real number", matrixName, row + 1, col + 1);
        }
        return value;
    } catch (...) {
        stream.quitf(_wa, "%s[%d][%d] is not a finite real number", matrixName, row + 1, col + 1);
    }
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken();
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}, {}};
    }

    Answer result;
    result.impossible = false;
    result.l.assign(n, vector<double>(n));
    result.u.assign(n, vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result.l[i][j] = readMatrixValue(stream, first, i == 0 && j == 0, "L", i, j);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result.u[i][j] = readMatrixValue(stream, "", false, "U", i, j);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after matrices");
    }

    for (int i = 0; i < n; ++i) {
        if (fabs(result.l[i][i] - 1.0) > ENTRY_EPS) {
            stream.quitf(_wa, "L[%d][%d] must be 1, found %.10f", i + 1, i + 1, result.l[i][i]);
        }
        if (fabs(result.u[i][i]) <= ZERO_EPS) {
            stream.quitf(_wa, "U[%d][%d] must be nonzero, found %.10f", i + 1, i + 1, result.u[i][i]);
        }
        for (int j = i + 1; j < n; ++j) {
            if (fabs(result.l[i][j]) > ENTRY_EPS) {
                stream.quitf(_wa, "L[%d][%d] must be zero, found %.10f", i + 1, j + 1, result.l[i][j]);
            }
        }
        for (int j = 0; j < i; ++j) {
            if (fabs(result.u[i][j]) > ENTRY_EPS) {
                stream.quitf(_wa, "U[%d][%d] must be zero, found %.10f", i + 1, j + 1, result.u[i][j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double got = 0.0;
            for (int k = 0; k < n; ++k) {
                got += result.l[i][k] * result.u[k][j];
            }
            if (fabs(got - a[i][j]) > PRODUCT_EPS) {
                stream.quitf(_wa,
                             "(L*U)[%d][%d] must equal A[%d][%d]=%.10f, found %.10f",
                             i + 1, j + 1, i + 1, j + 1, a[i][j], got);
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.assign(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = inf.readDouble();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail, "participant supplied a valid LU decomposition while jury reports impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant reports impossible while jury provides a decomposition");
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fabs(participant.l[i][j] - jury.l[i][j]) > ENTRY_EPS) {
                quitf(_wa, "L[%d][%d] differs from jury: expected %.10f, found %.10f",
                      i + 1, j + 1, jury.l[i][j], participant.l[i][j]);
            }
            if (fabs(participant.u[i][j] - jury.u[i][j]) > ENTRY_EPS) {
                quitf(_wa, "U[%d][%d] differs from jury: expected %.10f, found %.10f",
                      i + 1, j + 1, jury.u[i][j], participant.u[i][j]);
            }
        }
    }

    quitf(_ok, "valid LU decomposition");
}
