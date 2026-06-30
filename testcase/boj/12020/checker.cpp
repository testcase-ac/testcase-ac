#include "testlib.h"

#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

const long double ZERO_EPS = 1e-12L;
const long double ROUND_EPS = 0.0005L + 1e-12L;
const long double VALUE_LIMIT = 1e100L;

int n;
vector<vector<long double> > expectedL;
vector<vector<long double> > expectedU;

struct Claim {
    bool impossible;
};

long double parseRealToken(InStream& stream, TResult invalidResult, const string& token, const string& name) {
    char* end = nullptr;
    long double value = strtold(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0' || !isfinite(value)) {
        stream.quitf(invalidResult, "%s is not a finite real number: %s", name.c_str(), token.c_str());
    }
    if (fabsl(value) > VALUE_LIMIT) {
        stream.quitf(invalidResult, "%s is too large: %.17Lg", name.c_str(), value);
    }
    return value;
}

long double roundedToThree(long double value) {
    return roundl(value * 1000.0L) / 1000.0L;
}

void requireRoundedEntry(InStream& stream,
                         TResult invalidResult,
                         long double actual,
                         long double expected,
                         const char* matrixName,
                         int row,
                         int col) {
    long double roundedExpected = roundedToThree(expected);
    if (fabsl(actual - roundedExpected) > ROUND_EPS) {
        stream.quitf(invalidResult,
                     "%s[%d][%d] must round to %.3Lf, found %.10Lg",
                     matrixName,
                     row + 1,
                     col + 1,
                     roundedExpected,
                     actual);
    }
}

Claim readClaim(InStream& stream, TResult invalidResult, bool decompositionImpossible) {
    string first = stream.readToken();
    if (first == "-1") {
        if (!stream.seekEof()) {
            stream.quitf(invalidResult, "extra output after -1");
        }
        return {true};
    }

    if (decompositionImpossible) {
        stream.quitf(invalidResult, "LU decomposition is impossible; output must be -1");
    }

    long double firstValue = parseRealToken(stream, invalidResult, first, "L[1][1]");
    requireRoundedEntry(stream, invalidResult, firstValue, expectedL[0][0], "L", 0, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = (i == 0 ? 1 : 0); j < n; ++j) {
            string name = format("L[%d][%d]", i + 1, j + 1);
            long double value = parseRealToken(stream, invalidResult, stream.readToken(), name);
            requireRoundedEntry(stream, invalidResult, value, expectedL[i][j], "L", i, j);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string name = format("U[%d][%d]", i + 1, j + 1);
            long double value = parseRealToken(stream, invalidResult, stream.readToken(), name);
            requireRoundedEntry(stream, invalidResult, value, expectedU[i][j], "U", i, j);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after matrices");
    }

    return {false};
}

bool buildCanonicalLU(const vector<vector<long double> >& a) {
    expectedL.assign(n, vector<long double>(n, 0.0L));
    expectedU.assign(n, vector<long double>(n, 0.0L));

    for (int i = 0; i < n; ++i) {
        expectedL[i][i] = 1.0L;
    }

    expectedU[0][0] = a[0][0];
    if (fabsl(expectedU[0][0]) <= ZERO_EPS) {
        return false;
    }
    if (n > 1) {
        expectedU[0][1] = a[0][1];
    }

    for (int i = 1; i < n; ++i) {
        if (fabsl(expectedU[i - 1][i - 1]) <= ZERO_EPS) {
            return false;
        }
        expectedL[i][i - 1] = a[i][i - 1] / expectedU[i - 1][i - 1];
        expectedU[i][i] = a[i][i] - expectedL[i][i - 1] * expectedU[i - 1][i];
        if (fabsl(expectedU[i][i]) <= ZERO_EPS) {
            return false;
        }
        if (i + 1 < n) {
            expectedU[i][i + 1] = a[i][i + 1];
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    vector<vector<long double> > a(n, vector<long double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = inf.readDouble();
        }
    }

    bool possible = buildCanonicalLU(a);
    Claim jury = readClaim(ans, _fail, !possible);
    Claim participant = readClaim(ouf, _wa, !possible);

    if (jury.impossible) {
        if (participant.impossible) {
            if (possible) {
                quitf(_fail, "jury says impossible but canonical LU decomposition exists");
            }
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant supplied a valid LU decomposition while jury says impossible");
    }

    if (participant.impossible) {
        if (!possible) {
            quitf(_fail, "jury provides a decomposition while canonical LU decomposition is impossible");
        }
        quitf(_wa, "participant says impossible but jury provides a valid LU decomposition");
    }

    quitf(_ok, "valid LU decomposition");
}
