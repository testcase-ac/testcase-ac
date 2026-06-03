#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

string integerToken(long long value) {
    return to_string(value);
}

vector<long long> divisors(long long value) {
    value = llabs(value);
    vector<long long> result;
    for (long long d = 1; d * d <= value; ++d) {
        if (value % d == 0) {
            result.push_back(d);
            if (d * d != value) result.push_back(value / d);
        }
    }
    sort(result.begin(), result.end());
    return result;
}

long long smallNumber(bool allowZero = true) {
    int magnitude = rnd.wnext(21, -2);
    long long value = magnitude;
    if (rnd.next(2)) value = -value;
    if (!allowZero && value == 0) value = rnd.next(2) ? 1 : -1;
    return value;
}

void appendMulDivMod(vector<string>& tokens, long long& currentTerm) {
    int opKind = rnd.next(3);

    if (opKind == 0) {
        long long rhs = smallNumber(false);
        tokens.push_back("*");
        tokens.push_back(integerToken(rhs));
        currentTerm *= rhs;
        return;
    }

    if (opKind == 1) {
        if (currentTerm == 0) {
            long long rhs = smallNumber(false);
            tokens.push_back("/");
            tokens.push_back(integerToken(rhs));
            return;
        }

        vector<long long> choices = divisors(currentTerm);
        long long rhs = rnd.any(choices);
        if (rnd.next(2)) rhs = -rhs;
        tokens.push_back("/");
        tokens.push_back(integerToken(rhs));
        currentTerm /= rhs;
        return;
    }

    long long rhs = rnd.next(1, 20);
    if (rnd.next(2)) rhs = -rhs;
    tokens.push_back("%");
    tokens.push_back(integerToken(rhs));
    currentTerm %= rhs;
}

string joinTokens(const vector<string>& tokens) {
    string expression = tokens[0];
    for (int i = 1; i < (int)tokens.size(); ++i) {
        expression += " ";
        expression += tokens[i];
    }
    return expression;
}

string makeExpression(int mode) {
    vector<string> tokens;
    long long currentTerm = smallNumber();
    tokens.push_back(integerToken(currentTerm));

    int operations = 0;
    if (mode == 0) {
        operations = 0;
    } else if (mode == 1) {
        operations = rnd.next(1, 4);
    } else if (mode == 2) {
        operations = rnd.next(2, 6);
    } else if (mode == 3) {
        operations = rnd.next(3, 8);
    } else {
        operations = rnd.next(8, 18);
    }

    for (int i = 0; i < operations; ++i) {
        bool useHighPrecedence = false;
        if (mode == 2) {
            useHighPrecedence = true;
        } else if (mode == 1) {
            useHighPrecedence = false;
        } else {
            useHighPrecedence = rnd.next(100) < 60;
        }

        if (useHighPrecedence) {
            appendMulDivMod(tokens, currentTerm);
        } else {
            tokens.push_back(rnd.next(2) ? "+" : "-");
            currentTerm = smallNumber();
            tokens.push_back(integerToken(currentTerm));
        }
    }

    return joinTokens(tokens);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 14);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int mode;
        if (caseIndex < 5) {
            mode = caseIndex;
        } else {
            mode = rnd.next(5);
        }
        println(makeExpression(mode));
    }

    return 0;
}
