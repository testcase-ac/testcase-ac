#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static vector<string> splitBySpaces(const string& line) {
    vector<string> tokens;
    string token;
    for (char c : line) {
        if (c == ' ') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token.push_back(c);
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

static bool isCanonicalPositiveInteger(const string& token) {
    if (token.empty()) {
        return false;
    }
    if (token.size() > 1 && token[0] == '0') {
        return false;
    }
    for (char c : token) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

static int parseSmallPositiveInteger(const string& token) {
    int value = 0;
    for (char c : token) {
        value = value * 10 + (c - '0');
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    while (true) {
        string line = inf.readLine("[0-9\\-\\ ]{3,64}", "case_line");
        ensuref(!line.empty(), "line must not be empty");
        ensuref(line.front() != ' ' && line.back() != ' ',
                "line must not have leading or trailing spaces");

        vector<string> tokens = splitBySpaces(line);
        ensuref(tokens.size() == 2, "each line must contain exactly two tokens");

        if (tokens[0] == "-1" && tokens[1] == "-1") {
            inf.readEof();
            return 0;
        }

        ++testCases;
        ensuref(testCases <= 7000, "too many test cases: %d", testCases);

        ensuref(isCanonicalPositiveInteger(tokens[0]),
                "L must be a canonical positive integer, got '%s'",
                tokens[0].c_str());
        ensuref(isCanonicalPositiveInteger(tokens[1]),
                "U must be a canonical positive integer, got '%s'",
                tokens[1].c_str());

        int l = parseSmallPositiveInteger(tokens[0]);
        int u = parseSmallPositiveInteger(tokens[1]);
        ensuref(1 <= l && l <= u && u < 1000000,
                "expected 1 <= L <= U < 1000000, got L=%d U=%d", l, u);
    }
}
