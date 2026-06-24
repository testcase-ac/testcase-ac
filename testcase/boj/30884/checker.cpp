#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct ParsedAnswer {
    string brackets;
};

ParsedAnswer readAnswer(InStream& stream, const string& expectedBrackets) {
    string expression = stream.readToken("[()+1]{1,500000}", "expression");
    stream.readEoln();
    stream.readEof();

    vector<bool> needsOperand;
    needsOperand.push_back(true);

    string brackets;
    brackets.reserve(expectedBrackets.size());

    for (int i = 0; i < (int)expression.size(); ++i) {
        char ch = expression[i];

        if (ch == '1') {
            if (!needsOperand.back()) {
                stream.quitf(_wa, "unexpected operand at position %d", i + 1);
            }
            needsOperand.back() = false;
        } else if (ch == '+') {
            if (needsOperand.back()) {
                stream.quitf(_wa, "unexpected plus at position %d", i + 1);
            }
            needsOperand.back() = true;
        } else if (ch == '(') {
            if (!needsOperand.back()) {
                stream.quitf(_wa, "unexpected opening bracket at position %d", i + 1);
            }
            brackets.push_back(ch);
            needsOperand.push_back(true);
        } else if (ch == ')') {
            if (needsOperand.back()) {
                stream.quitf(_wa, "empty or incomplete bracketed expression ends at position %d", i + 1);
            }
            if (needsOperand.size() == 1) {
                stream.quitf(_wa, "unmatched closing bracket at position %d", i + 1);
            }
            brackets.push_back(ch);
            needsOperand.pop_back();
            needsOperand.back() = false;
        }
    }

    if (needsOperand.size() != 1) {
        stream.quitf(_wa, "unclosed opening bracket");
    }
    if (needsOperand.back()) {
        stream.quitf(_wa, "expression is incomplete");
    }
    if (brackets != expectedBrackets) {
        stream.quitf(_wa, "bracket projection does not match input");
    }

    return {brackets};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string expectedBrackets = inf.readToken("[()]{2,200000}", "S");
    inf.readEoln();
    inf.readEof();

    readAnswer(ans, expectedBrackets);
    readAnswer(ouf, expectedBrackets);

    quitf(_ok, "valid expression");
}
