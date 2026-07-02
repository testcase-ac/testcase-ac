#include "testlib.h"

#include <array>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

const int MAX_EXPR_LEN = 10000;
const array<long long, 5> MODS = {
    1000000007LL,
    1000000009LL,
    1000000033LL,
    1000000087LL,
    1000000093LL,
};

int n, m;
vector<int> goodBases, badBases;

struct Value {
    array<long long, MODS.size()> residue{};
    bool validDigits = true;
};

struct Parser {
    const string& s;
    size_t pos = 0;
    int base;
    InStream& stream;

    Parser(const string& expression, int base, InStream& stream)
        : s(expression), base(base), stream(stream) {}

    bool atEnd() const {
        return pos == s.size();
    }

    char peek() const {
        return atEnd() ? '\0' : s[pos];
    }

    Value parseExpression() {
        Value result = parseTerm();
        while (peek() == '+' || peek() == '-') {
            char op = s[pos++];
            Value rhs = parseTerm();
            result.validDigits = result.validDigits && rhs.validDigits;
            for (size_t i = 0; i < MODS.size(); ++i) {
                if (op == '+') {
                    result.residue[i] += rhs.residue[i];
                } else {
                    result.residue[i] -= rhs.residue[i];
                }
                result.residue[i] %= MODS[i];
                if (result.residue[i] < 0) {
                    result.residue[i] += MODS[i];
                }
            }
        }
        return result;
    }

    Value parseTerm() {
        Value result = parseFactor();
        while (peek() == '*') {
            ++pos;
            Value rhs = parseFactor();
            result.validDigits = result.validDigits && rhs.validDigits;
            for (size_t i = 0; i < MODS.size(); ++i) {
                result.residue[i] = result.residue[i] * rhs.residue[i] % MODS[i];
            }
        }
        return result;
    }

    Value parseFactor() {
        if (peek() == '-') {
            ++pos;
            Value value = parseFactor();
            for (size_t i = 0; i < MODS.size(); ++i) {
                if (value.residue[i] != 0) {
                    value.residue[i] = MODS[i] - value.residue[i];
                }
            }
            return value;
        }

        if (peek() == '(') {
            ++pos;
            Value value = parseExpression();
            if (peek() != ')') {
                stream.quitf(_wa, "missing closing parenthesis at position %d", int(pos + 1));
            }
            ++pos;
            return value;
        }

        if (!isdigit(static_cast<unsigned char>(peek()))) {
            stream.quitf(_wa, "expected digit, unary minus, or '(' at position %d", int(pos + 1));
        }

        Value value;
        while (isdigit(static_cast<unsigned char>(peek()))) {
            int digit = s[pos++] - '0';
            if (digit >= base) {
                value.validDigits = false;
            }
            for (size_t i = 0; i < MODS.size(); ++i) {
                value.residue[i] = (value.residue[i] * base + digit) % MODS[i];
            }
        }
        return value;
    }
};

static string readFormula(InStream& stream) {
    string formula;
    while (!stream.eof()) {
        char ch = stream.readChar();
        if (isspace(static_cast<unsigned char>(ch))) {
            continue;
        }
        if (formula.size() == MAX_EXPR_LEN) {
            stream.quitf(_wa, "formula has more than %d non-whitespace characters", MAX_EXPR_LEN);
        }
        if (!isdigit(static_cast<unsigned char>(ch)) &&
            ch != '+' && ch != '-' && ch != '*' && ch != '(' && ch != ')' && ch != '=') {
            stream.quitf(_wa, "invalid character '%c' in formula", ch);
        }
        formula.push_back(ch);
    }
    if (formula.empty()) {
        stream.quitf(_wa, "empty formula");
    }
    return formula;
}

static bool equalityHolds(const string& formula, int base, InStream& stream) {
    size_t eq = formula.find('=');
    if (eq == string::npos || formula.find('=', eq + 1) != string::npos) {
        stream.quitf(_wa, "formula must contain exactly one equality sign");
    }
    if (eq == 0 || eq + 1 == formula.size()) {
        stream.quitf(_wa, "both sides of equality must be non-empty");
    }

    string lhsText = formula.substr(0, eq);
    string rhsText = formula.substr(eq + 1);
    Parser lhsParser(lhsText, base, stream);
    Value lhs = lhsParser.parseExpression();
    if (!lhsParser.atEnd()) {
        stream.quitf(_wa, "unexpected token on left side at position %d", int(lhsParser.pos + 1));
    }

    Parser rhsParser(rhsText, base, stream);
    Value rhs = rhsParser.parseExpression();
    if (!rhsParser.atEnd()) {
        stream.quitf(_wa, "unexpected token on right side at position %d", int(eq + 2 + rhsParser.pos));
    }

    if (!lhs.validDigits || !rhs.validDigits) {
        return false;
    }
    return lhs.residue == rhs.residue;
}

struct Claim {
    string formula;
};

static Claim readClaim(InStream& stream) {
    string formula = readFormula(stream);
    for (int base : goodBases) {
        if (!equalityHolds(formula, base, stream)) {
            stream.quitf(_wa, "formula does not hold in required base %d", base);
        }
    }
    for (int base : badBases) {
        if (equalityHolds(formula, base, stream)) {
            stream.quitf(_wa, "formula holds in forbidden base %d", base);
        }
    }
    return {formula};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    goodBases.resize(n);
    badBases.resize(m);
    for (int i = 0; i < n; ++i) {
        goodBases[i] = inf.readInt();
    }
    for (int i = 0; i < m; ++i) {
        badBases[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);
    quitf(_ok, "valid formula with %d non-whitespace characters", int(participant.formula.size()));
}
