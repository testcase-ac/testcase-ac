#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_A = 10000000000LL;

long long makePalindrome(long long prefix, bool oddLength) {
    long long result = prefix;
    if (oddLength) prefix /= 10;
    while (prefix > 0) {
        result = result * 10 + prefix % 10;
        prefix /= 10;
    }
    return result;
}

long long randomPalindrome() {
    int digits = rnd.next(1, 10);
    int prefixDigits = (digits + 1) / 2;
    long long lo = 1;
    for (int i = 1; i < prefixDigits; ++i) lo *= 10;
    long long hi = lo * 10 - 1;
    return makePalindrome(rnd.next(lo, hi), digits % 2 == 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> values = {
        1, 2, 3, 6, 10, 11, 22, 121, 144, 242, 9999999999LL, MAX_A
    };

    int targetT = rnd.next(8, 30);
    while ((int)values.size() < targetT) {
        int mode = rnd.next(0, 6);
        long long a = 1;

        if (mode == 0) {
            a = rnd.next(1, 1000);
        } else if (mode == 1) {
            long long base = rnd.next(2, 100);
            int exponent = rnd.next(2, 8);
            for (int i = 0; i < exponent && a <= MAX_A / base; ++i) a *= base;
        } else if (mode == 2) {
            long long p = randomPalindrome();
            a = p <= MAX_A ? p : rnd.next(1, 1000000);
        } else if (mode == 3) {
            long long p = randomPalindrome();
            long long q = randomPalindrome();
            if (p > 0 && q > 0 && p <= MAX_A / q) {
                a = p * q;
            } else {
                a = rnd.next(1, 100000000);
            }
        } else if (mode == 4) {
            long long p = rnd.any(vector<long long>{2, 3, 5, 7, 11, 101, 1001});
            long long m = rnd.next(1, (int)min(1000000LL, MAX_A / p));
            a = p * m;
        } else if (mode == 5) {
            a = MAX_A - rnd.next(0, 1000000);
        } else {
            long long hi = rnd.any(vector<long long>{100LL, 10000LL, 1000000LL, MAX_A});
            a = rnd.next(1LL, hi);
        }

        values.push_back(max(1LL, min(MAX_A, a)));
    }

    shuffle(values.begin(), values.end());
    values.resize(targetT);

    println((int)values.size());
    for (long long a : values) println(a);

    return 0;
}
