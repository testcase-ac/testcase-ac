#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long digitSum(long long x) {
    long long s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single positive integer n <= 1e9, canonical decimal format
    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readEoln();

    // Problem guarantees: "you will be given a number n and must find the smallest
    // harshad number ≥ n". That implies that such a number always exists for the input.
    // Since n ≤ 1e9, we can validate this by actually searching forward a bit and
    // ensuring we find a Harshad number within a reasonable bound.
    //
    // In fact, Harshad numbers are infinite and dense, but we add a concrete check:
    // search from n upwards until we find a Harshad number, with a hard limit.
    const long long LIMIT = 2000000000LL; // generous upper bound for search
    long long x = n;
    bool found = false;
    while (x <= LIMIT) {
        long long s = digitSum(x);
        if (s != 0 && x % s == 0) {
            found = true;
            break;
        }
        ++x;
    }
    ensuref(found, "No Harshad number found >= n=%lld up to %lld; violates problem guarantee.", n, LIMIT);

    inf.readEof();
}
