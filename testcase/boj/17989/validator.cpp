#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

bool isTitleChar(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return c == ' ' || (uc < 128 && isalnum(uc));
}

long long parseCanonicalInteger(const string& token, long long lower, long long upper,
                                const char* name, int lineNo) {
    ensuref(!token.empty(), "line %d: %s is empty", lineNo, name);
    ensuref(token == "0" || token[0] != '0', "line %d: %s has leading zero: %s",
            lineNo, name, token.c_str());

    long long value = 0;
    for (char c : token) {
        ensuref('0' <= c && c <= '9', "line %d: %s contains non-digit character",
                lineNo, name);
        value = value * 10 + (c - '0');
        ensuref(value <= upper, "line %d: %s exceeds upper bound %lld", lineNo, name,
                upper);
    }

    ensuref(lower <= value, "line %d: %s is below lower bound %lld", lineNo, name,
            lower);
    return value;
}

void validateTitle(const string& title, int lineNo) {
    ensuref(1 <= static_cast<int>(title.size()) && static_cast<int>(title.size()) <= 20,
            "line %d: title length must be between 1 and 20", lineNo);
    for (char c : title) {
        ensuref(isTitleChar(c), "line %d: title contains invalid character", lineNo);
    }
}

void validateBookLine(const string& line, int lineNo) {
    ensuref(!line.empty() && line[0] == '"', "line %d: book title must start with quote",
            lineNo);

    size_t closeQuote = line.find('"', 1);
    ensuref(closeQuote != string::npos, "line %d: book title must end with quote", lineNo);
    string title = line.substr(1, closeQuote - 1);
    validateTitle(title, lineNo);

    ensuref(closeQuote + 1 < line.size() && line[closeQuote + 1] == ' ',
            "line %d: quoted title and page count must be separated by one space", lineNo);
    string pages = line.substr(closeQuote + 2);
    parseCanonicalInteger(pages, 1, 99999, "k_i", lineNo);
}

void validateGiftLine(const string& line, int lineNo) {
    size_t firstSpace = line.find(' ');
    ensuref(firstSpace != string::npos, "line %d: gift time must be followed by a space",
            lineNo);
    string time = line.substr(0, firstSpace);
    parseCanonicalInteger(time, 0, 1000000000LL, "t_j", lineNo);

    ensuref(firstSpace + 1 < line.size() && line[firstSpace + 1] == '"',
            "line %d: gift title must start with quote", lineNo);
    size_t closeQuote = line.find('"', firstSpace + 2);
    ensuref(closeQuote != string::npos, "line %d: gift title must end with quote", lineNo);
    string title = line.substr(firstSpace + 2, closeQuote - firstSpace - 2);
    validateTitle(title, lineNo);

    ensuref(closeQuote + 1 < line.size() && line[closeQuote + 1] == ' ',
            "line %d: quoted gift title and page count must be separated by one space",
            lineNo);
    string pages = line.substr(closeQuote + 2);
    parseCanonicalInteger(pages, 1, 99999, "k_j", lineNo);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 99999, "n");
    inf.readSpace();
    int m = inf.readInt(0, 99999, "m");
    inf.readSpace();
    inf.readInt(1, 99999, "k");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string line = inf.readLine("[^]*", "initial_book");
        validateBookLine(line, i + 2);
    }

    for (int j = 0; j < m; ++j) {
        string line = inf.readLine("[^]*", "gift_book");
        validateGiftLine(line, n + j + 2);
    }

    inf.readEof();
}
