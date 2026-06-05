#include "testlib.h"

#include <cctype>
#include <string>

using namespace std;

const long long LIMIT = 134217728LL;

long long parseOctalInteger(const string& token, const char* name) {
    ensuref(!token.empty(), "%s is empty", name);

    int start = 0;
    bool negative = false;
    if (token[0] == '-') {
        negative = true;
        start = 1;
        ensuref(start < (int)token.size(), "%s has only a minus sign", name);
    }

    ensuref(token[start] != '+', "%s has a plus sign", name);
    if (token[start] == '0') {
        ensuref(start + 1 == (int)token.size(), "%s has leading zeroes: %s", name, token.c_str());
    }

    long long value = 0;
    for (int i = start; i < (int)token.size(); ++i) {
        ensuref('0' <= token[i] && token[i] <= '7',
                "%s contains a non-octal digit: %s", name, token.c_str());
        value = value * 8 + (token[i] - '0');
        ensuref(value <= LIMIT,
                "%s is outside the octal magnitude bound: %s", name, token.c_str());
    }

    if (negative) {
        value = -value;
        ensuref(value != 0, "%s is negative zero", name);
    }

    ensuref(-LIMIT <= value && value <= LIMIT,
            "%s is outside [-1000000000_8, 1000000000_8]: %s", name, token.c_str());
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string expression = inf.readLine("[^]{1,32}", "expression");
    for (char c : expression) {
        ensuref(!isspace((unsigned char)c), "expression contains whitespace");
    }

    int operatorIndex = -1;
    for (int i = 1; i < (int)expression.size(); ++i) {
        char c = expression[i];
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            operatorIndex = i;
            break;
        }
    }

    ensuref(operatorIndex != -1, "expression has no operator: %s", expression.c_str());
    ensuref(operatorIndex + 1 < (int)expression.size(),
            "expression has no right operand: %s", expression.c_str());

    char op = expression[operatorIndex];
    string left = expression.substr(0, operatorIndex);
    string right = expression.substr(operatorIndex + 1);

    int rightOperatorSearchStart = operatorIndex + 1;
    if (expression[rightOperatorSearchStart] == '-') {
        ++rightOperatorSearchStart;
    }
    ensuref(expression.find_first_of("+-*/", rightOperatorSearchStart) == string::npos,
            "expression has more than one operator: %s", expression.c_str());
    ensuref(!(op == '+' && !right.empty() && right[0] == '-'),
            "operator form +- is not allowed: %s", expression.c_str());
    ensuref(!(op == '-' && !right.empty() && right[0] == '-'),
            "operator form -- is not allowed: %s", expression.c_str());

    parseOctalInteger(left, "A");
    parseOctalInteger(right, "B");

    inf.readEof();
}
