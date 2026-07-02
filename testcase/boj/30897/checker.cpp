#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>

#include <string>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

// Checker for the YES/NO zero-expression witness format in BOJ 30897.
int n;
vector<string> inputNumbers;

struct ParsedExpr {
    vector<cpp_int> terms;
    vector<char> addOps;
};

struct Claim {
    bool possible;
    string expression;
};

cpp_int parseNumberValue(const string& s) {
    cpp_int value = 0;
    for (char ch : s) {
        value *= 10;
        value += ch - '0';
    }
    return value;
}

void applyFactor(ParsedExpr& parsed, char op, const cpp_int& value) {
    if (op == '*') {
        parsed.terms.back() *= value;
    } else {
        parsed.addOps.push_back(op);
        parsed.terms.push_back(value);
    }
}

cpp_int finishValue(const ParsedExpr& parsed) {
    cpp_int value = parsed.terms[0];
    for (int i = 1; i < (int)parsed.terms.size(); ++i) {
        if (parsed.addOps[i - 1] == '+') {
            value += parsed.terms[i];
        } else {
            value -= parsed.terms[i];
        }
    }
    return value;
}

cpp_int parseFlatExpression(const vector<cpp_int>& values, const vector<char>& ops) {
    ParsedExpr parsed;
    parsed.terms.push_back(values[0]);
    for (int i = 0; i < (int)ops.size(); ++i) {
        applyFactor(parsed, ops[i], values[i + 1]);
    }
    return finishValue(parsed);
}

cpp_int evaluateExpression(InStream& stream, TResult invalidResult, const string& expr) {
    vector<char> ops;
    int numberIndex = 0;
    int pos = 0;
    int openBefore = -1;
    int closeAfter = -1;
    bool opened = false;
    bool closed = false;

    for (int term = 0; term < n; ++term) {
        if (pos < (int)expr.size() && expr[pos] == '(') {
            if (opened) {
                stream.quitf(invalidResult, "more than one opening parenthesis");
            }
            if (closed) {
                stream.quitf(invalidResult, "opening parenthesis appears after closing parenthesis");
            }
            opened = true;
            openBefore = term;
            ++pos;
        }

        const string& expected = inputNumbers[numberIndex];
        if (expr.compare(pos, expected.size(), expected) != 0) {
            stream.quitf(invalidResult, "number %d is not the expected value %s", term + 1,
                         expected.c_str());
        }
        pos += (int)expected.size();
        ++numberIndex;

        if (pos < (int)expr.size() && expr[pos] == ')') {
            if (!opened) {
                stream.quitf(invalidResult, "closing parenthesis appears before opening parenthesis");
            }
            if (closed) {
                stream.quitf(invalidResult, "more than one closing parenthesis");
            }
            closed = true;
            closeAfter = term;
            ++pos;
        }

        if (term + 1 == n) {
            if (pos != (int)expr.size()) {
                stream.quitf(invalidResult, "extra characters after the last number");
            }
        } else {
            if (pos >= (int)expr.size()) {
                stream.quitf(invalidResult, "missing operator after number %d", term + 1);
            }
            char op = expr[pos++];
            if (op != '+' && op != '-' && op != '*') {
                stream.quitf(invalidResult, "invalid operator after number %d", term + 1);
            }
            ops.push_back(op);
        }
    }

    if (opened != closed) {
        stream.quitf(invalidResult, "parentheses are not balanced");
    }

    vector<cpp_int> values(n);
    for (int i = 0; i < n; ++i) {
        values[i] = parseNumberValue(inputNumbers[i]);
    }

    if (opened) {
        vector<cpp_int> insideValues;
        vector<char> insideOps;
        for (int i = openBefore; i <= closeAfter; ++i) {
            insideValues.push_back(values[i]);
        }
        for (int i = openBefore; i < closeAfter; ++i) {
            insideOps.push_back(ops[i]);
        }
        cpp_int inside = parseFlatExpression(insideValues, insideOps);

        vector<cpp_int> collapsedValues;
        vector<char> collapsedOps;
        for (int i = 0; i < openBefore; ++i) {
            collapsedValues.push_back(values[i]);
            collapsedOps.push_back(ops[i]);
        }
        collapsedValues.push_back(inside);
        for (int i = closeAfter + 1; i < n; ++i) {
            collapsedOps.push_back(ops[i - 1]);
            collapsedValues.push_back(values[i]);
        }
        return parseFlatExpression(collapsedValues, collapsedOps);
    }

    return parseFlatExpression(values, ops);
}

Claim readClaim(InStream& stream, TResult invalidResult, bool requireWitnessValidation) {
    string verdict = stream.readToken("[A-Z]+", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(invalidResult, "extra output after NO");
        }
        return {false, ""};
    }
    if (verdict != "YES") {
        stream.quitf(invalidResult, "verdict must be YES or NO");
    }

    string expr = stream.readToken("[0-9()+\\-*]+", "expression");
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after expression");
    }

    if (requireWitnessValidation) {
        cpp_int value = evaluateExpression(stream, invalidResult, expr);
        if (value != 0) {
            stream.quitf(invalidResult, "expression value is not zero");
        }
    }
    return {true, expr};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    inputNumbers.resize(n);
    for (int i = 0; i < n; ++i) {
        inputNumbers[i] = inf.readToken();
    }

    Claim jury = readClaim(ans, _fail, true);
    Claim participant = readClaim(ouf, _wa, true);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a valid YES witness but participant answered NO");
        }
        quitf(_ok, "valid zero expression");
    }

    if (!participant.possible) {
        quitf(_ok, "both outputs report NO");
    }

    quitf(_fail, "participant found a valid zero expression while jury answered NO");
}
