#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

static vector<string> splitBySingleSpaces(const string& line) {
    vector<string> tokens;
    string token;
    for (char c : line) {
        if (c == ' ') {
            ensuref(!token.empty(), "empty token in expression line");
            tokens.push_back(token);
            token.clear();
        } else {
            token.push_back(c);
        }
    }
    ensuref(!token.empty(), "expression line has trailing space");
    tokens.push_back(token);
    return tokens;
}

static int readTenths(const string& token, int tc) {
    ensuref(!token.empty(), "testcase %d has an empty number", tc);

    int dotCount = 0;
    for (char c : token) {
        dotCount += (c == '.');
    }
    ensuref(dotCount <= 1, "testcase %d number has more than one decimal point: %s",
            tc, token.c_str());

    string integerPart = token;
    int fractional = 0;
    if (dotCount == 1) {
        size_t dot = token.find('.');
        ensuref(dot > 0 && dot + 2 == token.size(),
                "testcase %d decimal must have exactly one digit after the point: %s",
                tc, token.c_str());
        integerPart = token.substr(0, dot);
        ensuref(isdigit(static_cast<unsigned char>(token[dot + 1])),
                "testcase %d decimal fraction is not a digit: %s", tc, token.c_str());
        fractional = token[dot + 1] - '0';
    }

    ensuref(!integerPart.empty(), "testcase %d has an empty integer part", tc);
    ensuref(integerPart.size() == 1 || integerPart[0] != '0',
            "testcase %d number has a leading zero: %s", tc, token.c_str());

    int integer = 0;
    for (char c : integerPart) {
        ensuref(isdigit(static_cast<unsigned char>(c)),
                "testcase %d integer part is not numeric: %s", tc, token.c_str());
        integer = integer * 10 + (c - '0');
    }

    int tenths = integer * 10 + fractional;
    ensuref(0 <= tenths && tenths <= 1000,
            "testcase %d number is outside [0, 100]: %s", tc, token.c_str());
    return tenths;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        string line = inf.readLine("[^]+", "expression");
        ensuref(line.front() != ' ', "testcase %d expression has leading space", tc);

        vector<string> tokens = splitBySingleSpaces(line);
        ensuref(2 <= tokens.size() && tokens.size() <= 4,
                "testcase %d must have one number and one to three operators", tc);

        readTenths(tokens[0], tc);

        for (int i = 1; i < static_cast<int>(tokens.size()); ++i) {
            ensuref(tokens[i].size() == 1,
                    "testcase %d operator token %d is not one character", tc, i);
            char op = tokens[i][0];
            ensuref(op == '@' || op == '%' || op == '#',
                    "testcase %d has invalid operator token %d: %s",
                    tc, i, tokens[i].c_str());
        }
    }

    inf.readEof();
}
