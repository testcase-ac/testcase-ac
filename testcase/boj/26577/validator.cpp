#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

const int MAX_T = 100000;
const int MAX_EXPR_TOKENS = 1001;
const int MAX_TOTAL_EXPR_TOKENS = 5000000;
const long long MAX_ABS_NUMBER = 1000000000LL;
const __int128 MAX_ABS_INTERMEDIATE = (__int128)9000000000000000000LL;

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

long long parseIntegerToken(const string& token, int caseIndex, int tokenIndex) {
    ensuref(!token.empty(), "empty integer token in case %d at token %d", caseIndex, tokenIndex);

    int pos = 0;
    if (token[0] == '-') {
        ensuref(token.size() > 1, "bare '-' is not an integer in case %d at token %d",
                caseIndex, tokenIndex);
        pos = 1;
    }
    ensuref(token[pos] != '+', "integer has leading plus in case %d at token %d",
            caseIndex, tokenIndex);
    ensuref(token[pos] != '0' || pos + 1 == (int)token.size(),
            "integer has leading zero in case %d at token %d", caseIndex, tokenIndex);

    long long value = 0;
    for (int i = pos; i < (int)token.size(); ++i) {
        ensuref(isdigit((unsigned char)token[i]), "non-digit in integer in case %d at token %d",
                caseIndex, tokenIndex);
        value = value * 10 + (token[i] - '0');
        ensuref(value <= MAX_ABS_NUMBER, "integer magnitude too large in case %d at token %d",
                caseIndex, tokenIndex);
    }

    return pos == 1 ? -value : value;
}

vector<string> splitLine(const string& line, int caseIndex) {
    ensuref(!line.empty(), "empty expression line in case %d", caseIndex);
    ensuref(line.front() != ' ' && line.back() != ' ',
            "expression has leading or trailing space in case %d", caseIndex);

    vector<string> tokens;
    string current;
    for (char ch : line) {
        ensuref(ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
                        isdigit((unsigned char)ch),
                "invalid character in expression in case %d", caseIndex);
        if (ch == ' ') {
            ensuref(!current.empty(), "repeated spaces in case %d", caseIndex);
            tokens.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    ensuref(!current.empty(), "expression has trailing space in case %d", caseIndex);
    tokens.push_back(current);

    // CHECK: The statement gives no expression length bound; cap each expression to a
    // small odd token count so validation remains practical while preserving the grammar.
    ensuref((int)tokens.size() <= MAX_EXPR_TOKENS,
            "too many expression tokens in case %d: %d", caseIndex, (int)tokens.size());
    ensuref(tokens.size() % 2 == 1, "expression must alternate integers and operators in case %d",
            caseIndex);
    return tokens;
}

void ensureWithinIntermediateCap(__int128 value, int caseIndex) {
    // CHECK: The statement gives no numeric result bounds; cap intermediates to signed
    // 64-bit scale so validator arithmetic and generated counterexamples stay practical.
    ensuref(-MAX_ABS_INTERMEDIATE <= value && value <= MAX_ABS_INTERMEDIATE,
            "intermediate value too large in case %d", caseIndex);
}

void validateExpression(const vector<string>& tokens, int caseIndex) {
    vector<__int128> terms;
    vector<string> addOps;

    __int128 currentTerm = parseIntegerToken(tokens[0], caseIndex, 1);
    for (int i = 1; i < (int)tokens.size(); i += 2) {
        const string& op = tokens[i];
        ensuref(isOperator(op), "invalid operator in case %d at token %d", caseIndex, i + 1);
        __int128 rhs = parseIntegerToken(tokens[i + 1], caseIndex, i + 2);

        if (op == "*" || op == "/" || op == "%") {
            if (op == "*") {
                currentTerm *= rhs;
            } else {
                ensuref(rhs != 0, "division or modulo by zero in case %d at token %d",
                        caseIndex, i + 1);
                if (op == "/") {
                    ensuref(currentTerm % rhs == 0,
                            "division is not integral in case %d at token %d", caseIndex, i + 1);
                    currentTerm /= rhs;
                } else {
                    currentTerm %= rhs;
                }
            }
            ensureWithinIntermediateCap(currentTerm, caseIndex);
        } else {
            terms.push_back(currentTerm);
            addOps.push_back(op);
            currentTerm = rhs;
        }
    }
    terms.push_back(currentTerm);

    __int128 total = terms[0];
    for (int i = 0; i < (int)addOps.size(); ++i) {
        if (addOps[i] == "+") {
            total += terms[i + 1];
        } else {
            total -= terms[i + 1];
        }
        ensureWithinIntermediateCap(total, caseIndex);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for n; use the local default cap.
    int t = inf.readInt(1, MAX_T, "n");
    inf.readEoln();

    int totalExpressionTokens = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        string line = inf.readLine("[^]{1,10000}", "equation");
        vector<string> tokens = splitLine(line, caseIndex);
        totalExpressionTokens += (int)tokens.size();
        ensuref(totalExpressionTokens <= MAX_TOTAL_EXPR_TOKENS,
                "too many total expression tokens: %d", totalExpressionTokens);
        validateExpression(tokens, caseIndex);
    }

    inf.readEof();
}
