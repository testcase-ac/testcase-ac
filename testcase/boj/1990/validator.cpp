#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Check if x is a palindrome in base 10
bool isPalindrome(int x) {
    string s = to_string(x);
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

// Check if x is prime (for x >= 2, x <= 1e8)
bool isPrime(int x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    int r = (int)sqrt((long double)x);
    for (int d = 3; d <= r; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case, two integers on first line.
    int a = inf.readInt(5, 100000000, "a");
    inf.readSpace();
    int b = inf.readInt(5, 100000000, "b");
    inf.readEoln();

    ensuref(a < b, "Constraint violated: a (%d) must be < b (%d)", a, b);

    // Global property from statement:
    // "마지막 줄에는 -1을 출력한다." (The last line of output is -1)
    // and "a이상 b이하인 소수인 팰린드롬을 모두 구하는 프로그램".
    // There is no guarantee that a prime palindrome always exists in [a, b],
    // so no need to validate existence. No other hidden global constraints.

    // However, to be thorough with implied bounds, we can ensure that
    // the number of prime palindromes in [a, b] is reasonable (it is small).
    // We actually enumerate them and only use this as a sanity check,
    // without enforcing any extra constraints beyond feasibility.
    // Since b - a <= 1e8, a full scan is too heavy here, so we do NOT.
    // Thus, no further global numeric checks are required.

    inf.readEof();
}
