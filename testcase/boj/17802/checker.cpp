#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000000000LL;

int n;
long long x;

struct Claim {
    bool impossible;
};

long long parsePositiveToken(InStream& stream, const string& token, const string& name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name.c_str());
    }
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            stream.quitf(_wa, "%s is not a positive integer", name.c_str());
        }
    }

    long long value = 0;
    for (char ch : token) {
        int digit = ch - '0';
        if (value > (LIMIT - digit) / 10) {
            stream.quitf(_wa, "%s is too large", name.c_str());
        }
        value = value * 10 + digit;
    }
    if (value < 1) {
        stream.quitf(_wa, "%s must be positive", name.c_str());
    }
    return value;
}

long long readPositive(InStream& stream, const string& name) {
    return parsePositiveToken(stream, stream.readWord(), name);
}

Claim readClaim(InStream& stream) {
    string first = stream.readWord();
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible");
        }
        return {true};
    }

    vector<vector<long long>> rows(n);
    rows[0].push_back(parsePositiveToken(stream, first, "row[1][1]"));

    for (int row = 2; row <= n; ++row) {
        rows[row - 1].resize(row);
        for (int col = 1; col <= row; ++col) {
            rows[row - 1][col - 1] =
                readPositive(stream, format("row[%d][%d]", row, col));
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after pyramid");
    }

    if (rows[0][0] != x) {
        stream.quitf(_wa, "top value is %lld instead of %lld", rows[0][0], x);
    }

    for (int row = 2; row <= n; ++row) {
        for (int col = 1; col < row; ++col) {
            long long left = rows[row - 1][col - 1];
            long long right = rows[row - 1][col];
            if (left > LIMIT - right) {
                stream.quitf(_wa, "sum overflows at row %d column %d", row, col);
            }
            long long expected = left + right;
            long long actual = rows[row - 2][col - 1];
            if (actual != expected) {
                stream.quitf(_wa,
                             "row[%d][%d]=%lld, but row[%d][%d]+row[%d][%d]=%lld",
                             row - 1,
                             col,
                             actual,
                             row,
                             col,
                             row,
                             col + 1,
                             expected);
            }
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    x = inf.readLong();

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible && participant.impossible) {
        quitf(_ok, "both outputs claim impossible");
    }
    if (!jury.impossible && !participant.impossible) {
        quitf(_ok, "valid pyramid");
    }
    if (jury.impossible && !participant.impossible) {
        quitf(_fail, "participant found a valid pyramid while jury says impossible");
    }
    quitf(_wa, "participant says impossible but jury has a valid pyramid");
}
