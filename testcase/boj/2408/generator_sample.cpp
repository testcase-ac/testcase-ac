#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string pow10String(int zeros) {
    return string("1") + string(zeros, '0');
}

string smallNumber(bool allowZero = true) {
    int lo = allowZero ? -20 : -20;
    int hi = 20;
    int value = rnd.next(lo, hi);
    if (!allowZero) {
        while (value == 0) value = rnd.next(lo, hi);
    }
    return to_string(value);
}

string largeNumber() {
    int digits = rnd.next(30, 101);
    string value = digits == 101 ? pow10String(100) : string(1, char('1' + rnd.next(9)));
    for (int i = 1; i < digits && digits < 101; ++i) value.push_back(char('0' + rnd.next(10)));
    if (rnd.next(2) == 0) value.insert(value.begin(), '-');
    return value;
}

void printExpression(const vector<string>& nums, const vector<char>& ops) {
    println((int)nums.size());
    for (int i = 0; i < (int)nums.size(); ++i) {
        println(nums[i]);
        if (i < (int)ops.size()) println(string(1, ops[i]));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    vector<string> nums;
    vector<char> ops;

    if (mode == 0) {
        nums.push_back(rnd.next(2) == 0 ? smallNumber() : largeNumber());
    } else if (mode == 1) {
        int n = rnd.next(2, 10);
        nums.push_back(rnd.next(2) == 0 ? pow10String(100) : "-" + pow10String(100));
        for (int i = 1; i < n; ++i) {
            ops.push_back(rnd.any(string("+-*")));
            nums.push_back(rnd.next(3) == 0 ? largeNumber() : smallNumber());
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            if (i > 0) ops.push_back(rnd.any(string("+-*/")));
            bool divisor = i > 0 && ops.back() == '/';
            nums.push_back(smallNumber(!divisor));
        }
    } else {
        int n = rnd.next(3, 10);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                char op = rnd.any(string("+-*/"));
                ops.push_back(op);
            }
            bool divisor = i > 0 && ops.back() == '/';
            if (rnd.next(5) == 0 && !divisor) {
                nums.push_back(largeNumber());
            } else {
                nums.push_back(smallNumber(!divisor));
            }
        }
    }

    printExpression(nums, ops);
    return 0;
}
