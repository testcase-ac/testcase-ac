#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

namespace {

vector<string> splitBySingleSpaces(const string& content, const string& lineName) {
    // CHECK: Official sample 1 has a trailing space after N, so trailing spaces
    // are accepted on numeric lines while leading spaces and repeated separators
    // before another token remain invalid.
    ensuref(!content.empty(), "%s must not be empty", lineName.c_str());
    ensuref(content.front() != ' ', "%s has leading space", lineName.c_str());

    vector<string> tokens;
    string current;
    bool previousWasSpace = false;
    for (char ch : content) {
        ensuref(ch == ' ' || (ch >= '0' && ch <= '9') || ch == '-',
                "%s contains invalid character", lineName.c_str());

        if (ch == ' ') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            } else {
                ensuref(!previousWasSpace, "%s has internal repeated spaces", lineName.c_str());
            }
            previousWasSpace = true;
        } else {
            current.push_back(ch);
            previousWasSpace = false;
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
    }

    ensuref(!tokens.empty(), "%s must contain at least one number", lineName.c_str());
    return tokens;
}

int parseIntToken(const string& token, int low, int high, const string& name) {
    ensuref(!token.empty(), "%s is empty", name.c_str());

    int pos = 0;
    if (token[0] == '-') {
        ensuref(token.size() > 1, "%s has minus sign without digits", name.c_str());
        pos = 1;
    }
    ensuref(pos + 1 == static_cast<int>(token.size()) || token[pos] != '0',
            "%s has leading zero: %s", name.c_str(), token.c_str());

    long long value = 0;
    for (int i = pos; i < static_cast<int>(token.size()); ++i) {
        ensuref(token[i] >= '0' && token[i] <= '9',
                "%s is not a canonical integer: %s", name.c_str(), token.c_str());
        value = value * 10 + (token[i] - '0');
        ensuref(value <= 1000000LL, "%s is too large: %s", name.c_str(), token.c_str());
    }
    if (pos == 1) {
        value = -value;
    }

    ensuref(low <= value && value <= high,
            "%s=%lld is outside [%d, %d]", name.c_str(), value, low, high);
    return static_cast<int>(value);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<string> firstLine = splitBySingleSpaces(inf.readLine("[^]*", "first line"), "first line");
    ensuref(firstLine.size() == 1, "first line must contain exactly one integer");
    int n = parseIntToken(firstLine[0], 2, 400, "n");

    for (int row = 1; row <= n; ++row) {
        string lineName = "row " + to_string(row);
        vector<string> tokens = splitBySingleSpaces(inf.readLine("[^]*", lineName), lineName);
        ensuref(static_cast<int>(tokens.size()) == n,
                "%s must contain exactly %d integers, found %d",
                lineName.c_str(), n, static_cast<int>(tokens.size()));

        for (int col = 1; col <= n; ++col) {
            parseIntToken(tokens[col - 1], -1000, 1000,
                          "a_" + to_string(row) + "_" + to_string(col));
        }
    }

    inf.readEof();
}
