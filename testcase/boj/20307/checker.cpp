#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

using i128 = __int128_t;

struct Fraction {
    i128 num = 0;
    i128 den = 1;
};

int n, m;

i128 abs128(i128 value) {
    return value < 0 ? -value : value;
}

i128 gcd128(i128 a, i128 b) {
    a = abs128(a);
    b = abs128(b);
    while (b != 0) {
        i128 r = a % b;
        a = b;
        b = r;
    }
    return a;
}

string toString(i128 value) {
    if (value == 0) {
        return "0";
    }

    bool negative = value < 0;
    if (negative) {
        value = -value;
    }

    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    if (negative) {
        result.push_back('-');
    }
    reverse(result.begin(), result.end());
    return result;
}

string formatFraction(Fraction value) {
    if (value.num == 0) {
        return "0";
    }
    if (value.den == 1) {
        return toString(value.num);
    }
    return toString(value.num) + "/" + toString(value.den);
}

bool equalFraction(Fraction lhs, Fraction rhs) {
    return lhs.num == rhs.num && lhs.den == rhs.den;
}

bool isZero(Fraction value) {
    return value.num == 0;
}

i128 parseInteger(InStream& stream, const string& text, const char* fieldName) {
    if (text.empty()) {
        stream.quitf(_wa, "%s is empty", fieldName);
    }

    int pos = 0;
    bool negative = false;
    if (text[0] == '-') {
        negative = true;
        pos = 1;
        if (pos == (int)text.size()) {
            stream.quitf(_wa, "%s has no digits", fieldName);
        }
    } else if (text[0] == '+') {
        stream.quitf(_wa, "%s uses an explicit positive sign", fieldName);
    }

    if (pos + 1 < (int)text.size() && text[pos] == '0') {
        stream.quitf(_wa, "%s has a leading zero", fieldName);
    }

    i128 value = 0;
    for (int i = pos; i < (int)text.size(); ++i) {
        if (!isdigit((unsigned char)text[i])) {
            stream.quitf(_wa, "%s contains a non-digit character", fieldName);
        }
        value = value * 10 + (text[i] - '0');
    }

    if (negative) {
        value = -value;
    }
    if (value == 0 && negative) {
        stream.quitf(_wa, "%s is negative zero", fieldName);
    }
    return value;
}

Fraction parseFraction(InStream& stream, const string& token, int row, int col) {
    if (token.empty()) {
        stream.quitf(_wa, "entry (%d,%d) is empty", row + 1, col + 1);
    }

    int slash = -1;
    for (int i = 0; i < (int)token.size(); ++i) {
        if (token[i] == '/') {
            if (slash != -1) {
                stream.quitf(_wa, "entry (%d,%d) has multiple slashes: %s", row + 1, col + 1, token.c_str());
            }
            slash = i;
        }
    }

    string numerator = slash == -1 ? token : token.substr(0, slash);
    string denominator = slash == -1 ? "1" : token.substr(slash + 1);
    i128 num = parseInteger(stream, numerator, "numerator");
    i128 den = parseInteger(stream, denominator, "denominator");

    if (den <= 0) {
        stream.quitf(_wa, "entry (%d,%d) has non-positive denominator: %s", row + 1, col + 1, token.c_str());
    }
    if (slash != -1 && den == 1) {
        stream.quitf(_wa, "entry (%d,%d) has denominator 1: %s", row + 1, col + 1, token.c_str());
    }
    if (num == 0 && slash != -1) {
        stream.quitf(_wa, "entry (%d,%d) writes zero as a fraction: %s", row + 1, col + 1, token.c_str());
    }
    if (gcd128(num, den) != 1) {
        stream.quitf(_wa, "entry (%d,%d) is not reduced: %s", row + 1, col + 1, token.c_str());
    }

    return {num, den};
}

vector<vector<Fraction>> readMatrix(InStream& stream) {
    vector<vector<Fraction>> matrix(n, vector<Fraction>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            string token = stream.readToken("[^\\s]+", format("entry[%d][%d]", i + 1, j + 1).c_str());
            matrix[i][j] = parseFraction(stream, token, i, j);
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the %d by %d matrix", n, m);
    }
    return matrix;
}

int leadingColumn(const vector<Fraction>& row) {
    for (int j = 0; j < m; ++j) {
        if (!isZero(row[j])) {
            return j;
        }
    }
    return m;
}

void validateRref(InStream& stream, const vector<vector<Fraction>>& matrix) {
    int previousLead = -1;
    bool seenZeroRow = false;

    for (int i = 0; i < n; ++i) {
        int lead = leadingColumn(matrix[i]);
        if (lead == m) {
            seenZeroRow = true;
            continue;
        }
        if (seenZeroRow) {
            stream.quitf(_wa, "non-zero row %d appears below a zero row", i + 1);
        }
        if (lead <= previousLead) {
            stream.quitf(_wa, "leading entry in row %d is not right of the previous leading entry", i + 1);
        }
        if (!(matrix[i][lead].num == 1 && matrix[i][lead].den == 1)) {
            stream.quitf(_wa, "leading entry in row %d is %s, not 1", i + 1, formatFraction(matrix[i][lead]).c_str());
        }
        for (int r = 0; r < n; ++r) {
            if (r != i && !isZero(matrix[r][lead])) {
                stream.quitf(_wa,
                             "entry (%d,%d) is %s, but leading column %d must be zero outside row %d",
                             r + 1,
                             lead + 1,
                             formatFraction(matrix[r][lead]).c_str(),
                             lead + 1,
                             i + 1);
            }
        }
        previousLead = lead;
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    vector<vector<Fraction>> jury = readMatrix(ans);
    vector<vector<Fraction>> participant = readMatrix(ouf);

    validateRref(ans, jury);
    validateRref(ouf, participant);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!equalFraction(participant[i][j], jury[i][j])) {
                quitf(_wa,
                      "entry (%d,%d): expected %s, found %s",
                      i + 1,
                      j + 1,
                      formatFraction(jury[i][j]).c_str(),
                      formatFraction(participant[i][j]).c_str());
            }
        }
    }

    quitf(_ok, "RREF matrix matches the jury baseline");
}
