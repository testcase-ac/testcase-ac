#include "testlib.h"

#include <climits>
#include <deque>
#include <string>
#include <vector>

using namespace std;

const long long MIN_VALUE = LLONG_MIN;
const long long MAX_VALUE = LLONG_MAX;

int priority(char op) {
    return (op == '*' || op == '/') ? 2 : 1;
}

bool checkedApply(long long a, char op, long long b, long long& out) {
    if (op == '/' && b == 0) {
        return false;
    }

    __int128 result;
    if (op == '+') {
        result = (__int128)a + b;
    } else if (op == '-') {
        result = (__int128)a - b;
    } else if (op == '*') {
        result = (__int128)a * b;
    } else {
        if (a == MIN_VALUE && b == -1) {
            return false;
        }
        result = a / b;
    }

    if (result < (__int128)MIN_VALUE || (__int128)MAX_VALUE < result) {
        return false;
    }

    out = (long long)result;
    return true;
}

bool validEvaluation(vector<long long> numbers, vector<char> operators) {
    deque<long long> nums(numbers.begin(), numbers.end());
    deque<char> ops(operators.begin(), operators.end());

    while (!ops.empty()) {
        int frontPriority = priority(ops.front());
        int backPriority = priority(ops.back());
        bool takeFront = false;

        if (frontPriority > backPriority) {
            takeFront = true;
        } else if (frontPriority == backPriority) {
            long long frontValue;
            long long backValue;
            if (!checkedApply(nums[0], ops.front(), nums[1], frontValue)) {
                return false;
            }
            if (!checkedApply(nums[nums.size() - 2], ops.back(), nums.back(), backValue)) {
                return false;
            }
            takeFront = frontValue >= backValue;
        }

        long long value;
        if (takeFront) {
            if (!checkedApply(nums[0], ops.front(), nums[1], value)) {
                return false;
            }
            nums.pop_front();
            nums.pop_front();
            nums.push_front(value);
            ops.pop_front();
        } else {
            if (!checkedApply(nums[nums.size() - 2], ops.back(), nums.back(), value)) {
                return false;
            }
            nums.pop_back();
            nums.pop_back();
            nums.push_back(value);
            ops.pop_back();
        }
    }

    return true;
}

string numberToken(long long value, bool allowLeadingZeros) {
    bool negative = value < 0;
    string digits = to_string(negative ? -value : value);
    if (allowLeadingZeros) {
        int zeros = rnd.next(0, 3);
        digits = string(zeros, '0') + digits;
    }
    return negative ? "-" + digits : digits;
}

char randomOperator(int mode) {
    if (mode == 1) {
        return rnd.any(string("+-"));
    }
    if (mode == 2) {
        return rnd.any(string("*/"));
    }
    if (mode == 3) {
        return rnd.any(string("+--*/"));
    }
    return rnd.any(string("+-*/"));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    for (int attempt = 0; attempt < 10000; ++attempt) {
        int mode = rnd.next(0, 4);
        int count;
        if (mode == 0) {
            count = 1;
        } else if (mode == 2) {
            count = rnd.next(2, 8);
        } else {
            count = rnd.next(2, 18);
        }

        vector<long long> numbers;
        vector<char> operators;
        numbers.reserve(count);
        operators.reserve(count - 1);

        int limit = (mode == 2) ? 12 : rnd.next(5, 100);
        for (int i = 0; i < count; ++i) {
            long long value;
            if (i == 0 && rnd.next(0, 3) == 0) {
                value = -rnd.next(0, limit);
            } else if (mode == 2) {
                value = rnd.next(1, limit);
            } else if (mode == 4 && rnd.next(0, 4) == 0) {
                value = 0;
            } else {
                value = rnd.next(0, limit);
            }
            numbers.push_back(value);
        }

        for (int i = 0; i + 1 < count; ++i) {
            operators.push_back(randomOperator(mode));
        }

        if (!validEvaluation(numbers, operators)) {
            continue;
        }

        string expression = numberToken(numbers[0], mode == 4 || rnd.next(0, 5) == 0);
        for (int i = 0; i < (int)operators.size(); ++i) {
            expression += operators[i];
            expression += numberToken(numbers[i + 1], mode == 4 || rnd.next(0, 5) == 0);
        }

        println(expression);
        return 0;
    }

    println("1+1");
    return 0;
}
