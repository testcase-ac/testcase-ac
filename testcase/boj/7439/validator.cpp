#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <set>
#include <string>
#include <vector>
using namespace std;

int parseCanonicalInt(const string& token, int low, int high, const char* name) {
    ensuref(!token.empty(), "%s must not be empty", name);

    int pos = 0;
    if (token[0] == '-') {
        pos = 1;
        ensuref(pos < (int)token.size(), "%s has only a minus sign", name);
    }

    ensuref(token[pos] != '+', "%s must not have a plus sign", name);
    if (token[pos] == '0') {
        ensuref(pos + 1 == (int)token.size(), "%s has leading zero: %s", name, token.c_str());
    } else {
        ensuref(token[pos] >= '1' && token[pos] <= '9', "%s is not a canonical integer: %s", name, token.c_str());
    }

    long long value = 0;
    for (int i = pos; i < (int)token.size(); ++i) {
        ensuref(isdigit((unsigned char)token[i]), "%s contains a non-digit: %s", name, token.c_str());
        value = value * 10 + (token[i] - '0');
        ensuref(value <= 1000000000LL, "%s is too large: %s", name, token.c_str());
    }
    if (pos == 1) {
        value = -value;
    }

    ensuref(low <= value && value <= high, "%s=%lld is outside [%d, %d]", name, value, low, high);
    return (int)value;
}

vector<string> splitCoordinateLine(const string& line, int index) {
    ensuref(!line.empty(), "coordinate line %d must not be empty", index);
    ensuref(line[0] != ' ', "coordinate line %d has leading space", index);

    vector<string> tokens;
    string current;
    bool trailing = false;
    for (char ch : line) {
        ensuref(ch == ' ' || ch == '-' || isdigit((unsigned char)ch),
                "coordinate line %d contains invalid character", index);
        if (ch == ' ') {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            } else {
                trailing = true;
            }
        } else {
            ensuref(!trailing, "coordinate line %d has repeated spaces between coordinates", index);
            current.push_back(ch);
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
    }

    ensuref(tokens.size() == 2, "coordinate line %d must contain exactly two integers", index);
    return tokens;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 750, "n");
    inf.readEoln();

    set<pair<int, int>> locations;
    for (int i = 1; i <= n; ++i) {
        // CHECK: the official sample has one trailing space after a coordinate pair,
        // so coordinate lines allow trailing spaces while keeping one separator between x and y.
        vector<string> tokens = splitCoordinateLine(inf.readLine(), i);
        int x = parseCanonicalInt(tokens[0], -10000, 10000, "x_i");
        int y = parseCanonicalInt(tokens[1], -10000, 10000, "y_i");
        ensuref(locations.insert({x, y}).second, "duplicate town location at index %d: (%d, %d)", i, x, y);
    }

    int m = inf.readInt(0, 1000, "m");
    inf.readEoln();

    set<pair<int, int>> highways;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b, "highway %d connects a town to itself: %d", i, a);
        pair<int, int> highway = minmax(a, b);
        ensuref(highways.insert(highway).second, "duplicate highway at index %d: (%d, %d)", i, a, b);
    }

    inf.readEof();
}
