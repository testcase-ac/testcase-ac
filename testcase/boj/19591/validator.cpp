#include "testlib.h"

#include <climits>
#include <deque>
#include <string>
#include <vector>

using namespace std;

const long long MIN_VALUE = LLONG_MIN;
const long long MAX_VALUE = LLONG_MAX;

long long parseNumber(const string& s, int tokenIndex) {
    int pos = 0;
    bool negative = false;
    if (!s.empty() && s[0] == '-') {
        negative = true;
        pos = 1;
    }

    ensuref(pos < (int)s.size(), "number token %d has no digits", tokenIndex);

    __int128 value = 0;
    for (int i = pos; i < (int)s.size(); ++i) {
        ensuref('0' <= s[i] && s[i] <= '9',
                "number token %d contains a non-digit character", tokenIndex);
        value = value * 10 + (s[i] - '0');
        __int128 limit = negative ? -(__int128)MIN_VALUE : (__int128)MAX_VALUE;
        ensuref(value <= limit, "number token %d is outside signed 64-bit range",
                tokenIndex);
    }

    if (negative) {
        value = -value;
    }
    return (long long)value;
}

int priority(char op) {
    return (op == '*' || op == '/') ? 2 : 1;
}

long long checkedApply(long long a, char op, long long b) {
    ensuref(op != '/' || b != 0, "division by zero during evaluation");

    __int128 result;
    if (op == '+') {
        result = (__int128)a + b;
    } else if (op == '-') {
        result = (__int128)a - b;
    } else if (op == '*') {
        result = (__int128)a * b;
    } else {
        ensuref(!(a == MIN_VALUE && b == -1),
                "division result is outside signed 64-bit range");
        result = a / b;
    }

    ensuref((__int128)MIN_VALUE <= result && result <= (__int128)MAX_VALUE,
            "intermediate result is outside signed 64-bit range");
    return (long long)result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string expr = inf.readLine("[0-9+\\-*/]{1,1000000}", "expression");
    inf.readEof();

    vector<string> numberTokens;
    vector<char> operators;

    int pos = 0;
    int numberIndex = 1;
    if (expr[pos] == '-') {
        ++pos;
        ensuref(pos < (int)expr.size() && '0' <= expr[pos] && expr[pos] <= '9',
                "leading minus must be followed by a digit");
        while (pos < (int)expr.size() && '0' <= expr[pos] && expr[pos] <= '9') {
            ++pos;
        }
        numberTokens.push_back(expr.substr(0, pos));
        ++numberIndex;
    } else {
        ensuref('0' <= expr[pos] && expr[pos] <= '9',
                "expression must start with a number");
        int start = pos;
        while (pos < (int)expr.size() && '0' <= expr[pos] && expr[pos] <= '9') {
            ++pos;
        }
        numberTokens.push_back(expr.substr(start, pos - start));
        ++numberIndex;
    }

    while (pos < (int)expr.size()) {
        char op = expr[pos++];
        ensuref(op == '+' || op == '-' || op == '*' || op == '/',
                "operator expected before number token %d", numberIndex);
        ensuref(pos < (int)expr.size() && '0' <= expr[pos] && expr[pos] <= '9',
                "operator at position %d is not followed by a number", pos);

        int start = pos;
        while (pos < (int)expr.size() && '0' <= expr[pos] && expr[pos] <= '9') {
            ++pos;
        }

        operators.push_back(op);
        numberTokens.push_back(expr.substr(start, pos - start));
        ++numberIndex;
    }

    ensuref(numberTokens.size() == operators.size() + 1,
            "numbers and operators must alternate");

    deque<long long> numbers;
    deque<char> ops;
    for (int i = 0; i < (int)numberTokens.size(); ++i) {
        numbers.push_back(parseNumber(numberTokens[i], i + 1));
    }
    for (char op : operators) {
        ops.push_back(op);
    }

    while (!ops.empty()) {
        bool takeFront = false;
        int frontPriority = priority(ops.front());
        int backPriority = priority(ops.back());
        if (frontPriority > backPriority) {
            takeFront = true;
        } else if (frontPriority == backPriority) {
            long long frontValue = checkedApply(numbers[0], ops.front(), numbers[1]);
            long long backValue =
                checkedApply(numbers[numbers.size() - 2], ops.back(), numbers.back());
            takeFront = frontValue >= backValue;
        }

        if (takeFront) {
            long long value = checkedApply(numbers[0], ops.front(), numbers[1]);
            numbers.pop_front();
            numbers.pop_front();
            numbers.push_front(value);
            ops.pop_front();
        } else {
            long long value =
                checkedApply(numbers[numbers.size() - 2], ops.back(), numbers.back());
            numbers.pop_back();
            numbers.pop_back();
            numbers.push_back(value);
            ops.pop_back();
        }
    }

    return 0;
}
