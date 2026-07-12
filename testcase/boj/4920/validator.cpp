#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

namespace {

constexpr int kMinN = 4;
constexpr int kMaxN = 100;
constexpr int kMinValue = -1000000;
constexpr int kMaxValue = 1000000;
constexpr int kMaxCases = 100000;

const string& requireNoEdgeSpaces(const string& line, const char* name) {
    ensuref(!line.empty(), "%s line must not be empty", name);
    ensuref(line.front() != ' ', "%s line has leading space", name);
    ensuref(line.back() != ' ', "%s line has trailing space", name);
    return line;
}

int parseIntToken(const string& token, int low, int high, const char* name) {
    ensuref(!token.empty(), "%s is empty", name);

    size_t pos = 0;
    if (token[pos] == '-') {
        ++pos;
        ensuref(pos < token.size(), "%s has only a sign", name);
    }

    ensuref(pos < token.size() && isdigit(static_cast<unsigned char>(token[pos])),
            "%s is not an integer: %s", name, token.c_str());

    long long value = 0;
    for (; pos < token.size(); ++pos) {
        ensuref(isdigit(static_cast<unsigned char>(token[pos])),
                "%s is not an integer: %s", name, token.c_str());
        value = value * 10 + (token[pos] - '0');
        ensuref(value <= 1000000000LL, "%s is too large: %s", name, token.c_str());
    }

    if (token[0] == '-') {
        value = -value;
    }
    ensuref(low <= value && value <= high, "%s out of range: %lld", name, value);
    return static_cast<int>(value);
}

int parseSingleIntLine(const string& line, int low, int high, const char* name) {
    const string& content = requireNoEdgeSpaces(line, name);
    ensuref(content.find(' ') == string::npos, "%s line has extra tokens", name);
    return parseIntToken(content, low, high, name);
}

vector<int> parseGridRow(const string& line, int n, int rowIndex) {
    const string& content = requireNoEdgeSpaces(line, "grid row");
    vector<int> values;

    size_t pos = 0;
    while (pos < content.size()) {
        size_t next = content.find(' ', pos);
        string token = content.substr(pos, next == string::npos ? string::npos : next - pos);
        ensuref(!token.empty(), "row %d has an empty value", rowIndex);
        values.push_back(parseIntToken(token, kMinValue, kMaxValue, "grid value"));
        if (next == string::npos) {
            break;
        }
        pos = content.find_first_not_of(' ', next);
        ensuref(pos != string::npos, "row %d has trailing spaces", rowIndex);
    }

    ensuref(static_cast<int>(values.size()) == n,
            "row %d has %d values, expected %d", rowIndex, static_cast<int>(values.size()), n);
    return values;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        string line = inf.readLine("[^]+", "N line");
        int n = parseSingleIntLine(line, 0, kMaxN, "N");
        if (n == 0) {
            ensuref(caseCount > 0, "input must contain at least one test case");
            break;
        }

        ++caseCount;
        ensuref(caseCount <= kMaxCases, "too many test cases");
        ensuref(n >= kMinN, "N out of range: %d", n);

        for (int row = 1; row <= n; ++row) {
            parseGridRow(inf.readLine("[^]+", "grid row"), n, row);
        }
    }

    inf.readEof();
}
