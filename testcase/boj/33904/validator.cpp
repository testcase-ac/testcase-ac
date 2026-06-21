#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

bool isVariable(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

void validateForLine(const string& line, int depth) {
    ensuref((int)line.size() == depth + 27,
            "for line %d has invalid length: %d", depth + 1, (int)line.size());

    for (int i = 0; i < depth; ++i) {
        ensuref(line[i] == ' ', "line %d indentation mismatch at column %d", depth + 1, i + 1);
    }

    const string prefix = "for (int ";
    const string middle = " = 1; ";
    const string suffix = " < 9; ";
    const string tail = "++)";

    int pos = depth;
    ensuref(line.compare(pos, prefix.size(), prefix) == 0,
            "line %d must start with for declaration", depth + 1);
    pos += (int)prefix.size();

    char variable = line[pos++];
    ensuref(isVariable(variable), "line %d variable must be one alphabet letter", depth + 1);

    ensuref(line.compare(pos, middle.size(), middle) == 0,
            "line %d has invalid initializer", depth + 1);
    pos += (int)middle.size();

    ensuref(line[pos++] == variable,
            "line %d condition variable differs from declared variable", depth + 1);

    ensuref(line.compare(pos, suffix.size(), suffix) == 0,
            "line %d has invalid loop bound", depth + 1);
    pos += (int)suffix.size();

    ensuref(line[pos++] == variable,
            "line %d increment variable differs from declared variable", depth + 1);

    ensuref(line.compare(pos, tail.size(), tail) == 0,
            "line %d has invalid increment suffix", depth + 1);
}

void validateExpressionLine(const string& line, int depth) {
    ensuref((int)line.size() >= depth + 1,
            "expression line must contain at least one expression character");

    for (int i = 0; i < depth; ++i) {
        ensuref(line[i] == ' ', "expression indentation mismatch at column %d", i + 1);
    }

    string expression = line.substr(depth);
    ensuref(1 <= (int)expression.size() && (int)expression.size() <= 20,
            "expression length must be between 1 and 20: %d", (int)expression.size());
    ensuref(expression.front() != ' ' && expression.back() != ' ',
            "expression must not start or end with a space");

    for (int i = 0; i < (int)expression.size(); ++i) {
        unsigned char c = expression[i];
        ensuref(32 <= c && c <= 126,
                "expression character at position %d is outside ASCII 32..126", i + 1);
        if (i > 0) {
            ensuref(!(isVariable(expression[i - 1]) && isVariable(expression[i])),
                    "expression has consecutive alphabet letters at positions %d and %d", i, i + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<string> lines;
    string line;
    while (true) {
        char c = inf.readChar();
        if (c == char(-1)) {
            ensuref(line.empty(), "input must end immediately after the final newline");
            break;
        }
        ensuref(c != '\r', "CR line endings are not allowed");
        if (c == '\n') {
            lines.push_back(line);
            ensuref(lines.size() <= 500, "code must be at most 500 lines");
            line.clear();
        } else {
            line.push_back(c);
            ensuref(line.size() <= 600, "line is too long");
        }
    }

    ensuref(2 <= (int)lines.size() && (int)lines.size() <= 500,
            "code must contain at least one for line and one expression line");

    for (int i = 0; i + 1 < (int)lines.size(); ++i) {
        validateForLine(lines[i], i);
    }
    validateExpressionLine(lines.back(), (int)lines.size() - 1);

    inf.readEof();
}
