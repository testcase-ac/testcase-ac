#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const long long LIMIT_ABC = 1000000000000000000LL;
static const long long LIMIT_D_READ = 3000000000000000000LL;

static __int128 productCapped(const array<long long, 3>& values) {
    const __int128 limit = (__int128)numeric_limits<long long>::max();
    __int128 product = 1;
    for (long long value : values) {
        if (product > limit / value) {
            return limit + 1;
        }
        product *= value;
    }
    return product;
}

static __int128 maxRemainingVolumeCapped(long long A, long long B, long long C, long long D) {
    array<long long, 3> cap = {A, B, C};
    sort(cap.begin(), cap.end());

    long long remaining = A + B + C - D;
    array<long long, 3> side = {0, 0, 0};

    if (remaining <= cap[0] * 3) {
        long long q = remaining / 3;
        int r = (int)(remaining % 3);
        side = {q, q, q};
        for (int i = 0; i < r; ++i) {
            ++side[i];
        }
        return productCapped(side);
    }

    side[0] = cap[0];
    remaining -= cap[0];
    if (remaining <= cap[1] * 2) {
        long long q = remaining / 2;
        int r = (int)(remaining % 2);
        side[1] = q + r;
        side[2] = q;
        return productCapped(side);
    }

    side[1] = cap[1];
    side[2] = remaining - cap[1];
    return productCapped(side);
}

static vector<string> splitStrictSpaceLine(const string& line, const string& name) {
    ensuref(!line.empty(), "%s must not be empty", name.c_str());
    ensuref(line.front() != ' ' && line.back() != ' ',
            "%s must not have leading or trailing spaces", name.c_str());

    vector<string> tokens;
    string token;
    for (char ch : line) {
        if (ch == ' ') {
            ensuref(!token.empty(), "%s must not contain repeated spaces", name.c_str());
            tokens.push_back(token);
            token.clear();
        } else {
            token.push_back(ch);
        }
    }
    ensuref(!token.empty(), "%s must not contain repeated spaces", name.c_str());
    tokens.push_back(token);
    return tokens;
}

static long long parseUnsignedLongBounded(const string& token, long long low, long long high,
                                          const string& name, int tc) {
    ensuref(!token.empty(), "%s is empty in test case %d", name.c_str(), tc);
    ensuref(token.size() == 1 || token[0] != '0',
            "%s has leading zeroes in test case %d: %s",
            name.c_str(), tc, token.c_str());
    __int128 value = 0;
    for (char ch : token) {
        ensuref('0' <= ch && ch <= '9',
                "%s is not a nonnegative integer in test case %d: %s",
                name.c_str(), tc, token.c_str());
        value = value * 10 + (ch - '0');
        ensuref(value <= (__int128)high,
                "%s exceeds upper bound in test case %d: %s",
                name.c_str(), tc, token.c_str());
    }

    ensuref(value >= low && value <= high,
            "%s out of range in test case %d: %s", name.c_str(), tc, token.c_str());
    return (long long)value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        string line = inf.readLine("[^]*", "case_or_blank_line");
        // CHECK: Korean and English text mention blank lines around test cases,
        // but the official sample has no blank separators. Accept either zero
        // or one blank line before each case.
        if (line.empty()) {
            line = inf.readLine("[^]*", "case_line");
        }

        vector<string> tokens = splitStrictSpaceLine(line, "case line");
        ensuref(tokens.size() == 4,
                "Expected 4 integers in test case %d, got %d",
                tc + 1, (int)tokens.size());

        long long A = parseUnsignedLongBounded(tokens[0], 1LL, LIMIT_ABC, "A", tc + 1);
        long long B = parseUnsignedLongBounded(tokens[1], 1LL, LIMIT_ABC, "B", tc + 1);
        long long C = parseUnsignedLongBounded(tokens[2], 1LL, LIMIT_ABC, "C", tc + 1);
        long long D = parseUnsignedLongBounded(tokens[3], 0LL, LIMIT_D_READ, "D", tc + 1);

        // Constraint: 0 <= D <= A + B + C - 3
        __int128 sum = (__int128)A + (__int128)B + (__int128)C;
        __int128 maxD128 = sum - 3;
        // Since A,B,C >= 1, we have sum >= 3, so maxD128 >= 0.
        ensuref(maxD128 >= 0,
                "Internal error: A+B+C-3 is negative in test case %d (A=%lld,B=%lld,C=%lld)",
                tc + 1, A, B, C);
        long long maxD = (long long)maxD128;
        ensuref(D <= maxD,
                "D out of allowed range 0..A+B+C-3 in test case %d: D=%lld, max allowed=%lld (A=%lld,B=%lld,C=%lld)",
                tc + 1, D, maxD, A, B, C);

        __int128 answer = maxRemainingVolumeCapped(A, B, C, D);
        __int128 maxLL = numeric_limits<long long>::max();
        ensuref(answer <= maxLL,
                "Maximum remaining volume does not fit in signed 64-bit integer in test case %d (A=%lld,B=%lld,C=%lld,D=%lld)",
                tc + 1, A, B, C, D);
    }

    inf.readEof();
}
