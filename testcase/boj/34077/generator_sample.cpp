#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeExpression(int n, int mode) {
    string expression;
    expression.reserve(2 * n + 1);

    vector<char> digits(n + 1);
    for (char& digit : digits) {
        digit = char('0' + rnd.next(0, 9));
    }

    vector<char> ops(n, '+');
    if (mode == 0) {
        fill(ops.begin(), ops.end(), '+');
    } else if (mode == 1) {
        fill(ops.begin(), ops.end(), '-');
    } else if (mode == 2) {
        for (char& op : ops) {
            op = rnd.next(0, 1) ? '+' : '-';
        }
    } else if (mode == 3) {
        fill(ops.begin(), ops.end(), '+');
        ops[n - 1] = '-';
    } else {
        int firstMinus = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i < firstMinus) {
                ops[i] = '+';
            } else {
                ops[i] = rnd.next(0, 1) ? '+' : '-';
            }
        }
        for (int i = firstMinus + 2; i <= n; ++i) {
            digits[i] = rnd.next(0, 3) == 0 ? char('0' + rnd.next(1, 9)) : '0';
        }
    }

    for (int i = 0; i <= n; ++i) {
        expression += digits[i];
        if (i < n) {
            expression += ops[i];
        }
    }
    return expression;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    vector<pair<int, string>> cases;
    cases.reserve(t);

    int totalN = 0;
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        int remainingCases = t - caseIndex;
        int maxN = min(25, 100000 - totalN - (remainingCases - 1));
        int n = rnd.next(1, maxN);
        int mode = rnd.next(0, 4);

        cases.push_back({n, makeExpression(n, mode)});
        totalN += n;
    }

    println(t);
    for (const auto& testCase : cases) {
        println(testCase.first);
        println(testCase.second);
    }

    return 0;
}
