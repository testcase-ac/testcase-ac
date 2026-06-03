#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

static int parseLine(const string& line, int lineNumber) {
    ensuref(line.size() >= 3, "line %d is too short", lineNumber);
    ensuref(line[0] == '1' && line[1] == '/', "line %d must start with 1/", lineNumber);

    string value = line.substr(2);
    ensuref(!value.empty(), "line %d has empty denominator", lineNumber);
    ensuref(value == "0" || value[0] != '0', "line %d has a leading zero denominator", lineNumber);

    int n = 0;
    for (char ch : value) {
        ensuref('0' <= ch && ch <= '9', "line %d denominator contains a non-digit", lineNumber);
        n = n * 10 + (ch - '0');
        ensuref(n <= 10000, "line %d denominator exceeds 10000", lineNumber);
    }
    ensuref(1 <= n && n <= 10000, "line %d denominator is out of range", lineNumber);
    return n;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<string> lines;
    string current;
    while (!inf.eof()) {
        char ch = inf.readChar();
        ensuref(ch == '\n' || (' ' <= ch && ch <= '~'), "input contains a non-printable character");
        if (ch == '\n') {
            lines.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }

    ensuref(current.empty(), "input must end with a newline");
    ensuref(!lines.empty(), "input must contain at least one test case");
    // CHECK: The statement gives no test-case count or upper bound; use the local default cap.
    ensuref(lines.size() <= 100000, "too many test cases: %d", int(lines.size()));

    for (int i = 0; i < int(lines.size()); ++i) {
        parseLine(lines[i], i + 1);
    }

    inf.readEof();
}
