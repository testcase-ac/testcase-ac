#include "testlib.h"

#include <string>

using namespace std;

bool isDieSides(int sides) {
    return sides == 4 || sides == 6 || sides == 8 || sides == 12 || sides == 20;
}

void parsePositiveInt(const string& expression, int& pos, int& parsedValue, int low, int high, const char* field) {
    int start = pos;
    int value = 0;
    while (pos < int(expression.size()) && expression[pos] >= '0' && expression[pos] <= '9') {
        value = value * 10 + expression[pos] - '0';
        ++pos;
    }

    ensuref(pos > start, "%s is missing at position %d in expression '%s'",
            field, start + 1, expression.c_str());

    string token = expression.substr(start, pos - start);
    ensuref(token == "0" || token[0] != '0',
            "%s has leading zero at position %d in expression '%s'",
            field, start + 1, expression.c_str());
    ensuref(low <= value && value <= high,
            "%s=%d is outside [%d, %d] at position %d in expression '%s'",
            field, value, low, high, start + 1, expression.c_str());

    parsedValue = value;
}

void validateExpression(const string& expression) {
    ensuref(!expression.empty(), "dice expression must not be empty");
    ensuref(expression[0] != '+' && expression[0] != '-',
            "dice expression must start with a term: '%s'", expression.c_str());

    int totalDice = 0;
    int pos = 0;

    while (pos < int(expression.size())) {
        int termStart = pos;
        int firstNumber = 0;
        parsePositiveInt(expression, pos, firstNumber, 1, 10, "term value");

        if (pos < int(expression.size()) && expression[pos] == 'd') {
            ensuref(firstNumber <= 6,
                    "die count %d is outside [1, 6] at position %d in expression '%s'",
                    firstNumber, termStart + 1, expression.c_str());
            ++pos;

            int sidesStart = pos;
            int sides = 0;
            parsePositiveInt(expression, pos, sides, 1, 20, "die sides");
            ensuref(isDieSides(sides),
                    "die sides %d at position %d must be one of 4, 6, 8, 12, or 20 in expression '%s'",
                    sides, sidesStart + 1, expression.c_str());

            totalDice += firstNumber;
            ensuref(totalDice <= 6,
                    "total dice count %d exceeds 6 in expression '%s'",
                    totalDice, expression.c_str());
        }

        if (pos == int(expression.size())) {
            break;
        }

        ensuref(expression[pos] == '+' || expression[pos] == '-',
                "expected '+' or '-' at position %d in expression '%s'",
                pos + 1, expression.c_str());
        ++pos;
        ensuref(pos < int(expression.size()),
                "dice expression must not end with an operator: '%s'", expression.c_str());
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    int totalExpressionLength = 0;
    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        inf.readInt(0, 100, "T");
        inf.readSpace();
        string expression = inf.readToken("[^ ]{1,100000}", "X");
        inf.readEoln();

        // CHECK: The statement omits a maximum length for X; cap aggregate expression text at 1,000,000 bytes.
        totalExpressionLength += int(expression.size());
        ensuref(totalExpressionLength <= 1000000,
                "aggregate dice expression length exceeds 1000000");

        validateExpression(expression);
    }

    inf.readEof();
}
