#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string randomDigits(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s.push_back(char('0' + rnd.next(0, 9)));
    return s;
}

string repeatedDigit(int n, int digit) {
    return string(n, char('0' + digit));
}

string shiftedDigits(const string& base, int delta) {
    string result = base;
    for (char& c : result) c = char('0' + (c - '0' + delta) % 10);
    return result;
}

string alternatingDigits(int n, int a, int b) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s.push_back(char('0' + (i % 2 == 0 ? a : b)));
    return s;
}

string walkDigits(int n, int start, int step) {
    string s;
    s.reserve(n);
    int value = start;
    for (int i = 0; i < n; ++i) {
        s.push_back(char('0' + value));
        value = (value + step) % 10;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(80, 160);
    } else {
        n = rnd.next(3, 40);
    }

    string current;
    string target;

    if (mode == 0) {
        current = randomDigits(n);
        target = randomDigits(n);
    } else if (mode == 1) {
        current = repeatedDigit(n, rnd.next(0, 9));
        target = repeatedDigit(n, rnd.next(0, 9));
    } else if (mode == 2) {
        current = randomDigits(n);
        target = shiftedDigits(current, rnd.next(1, 9));
    } else if (mode == 3) {
        int a = rnd.next(0, 9);
        int b = rnd.next(0, 9);
        int c = rnd.next(0, 9);
        int d = rnd.next(0, 9);
        current = alternatingDigits(n, a, b);
        target = alternatingDigits(n, c, d);
    } else if (mode == 4) {
        current = walkDigits(n, rnd.next(0, 9), rnd.next(1, 9));
        target = walkDigits(n, rnd.next(0, 9), rnd.next(1, 9));
    } else if (mode == 5) {
        current = randomDigits(n);
        target = current;
        int changes = rnd.next(1, max(1, n / 3));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, n - 1);
            target[pos] = char('0' + rnd.next(0, 9));
        }
    } else if (mode == 6) {
        current = randomDigits(n);
        target = current;
        reverse(target.begin(), target.end());
    } else {
        current = repeatedDigit(n, 0);
        target = repeatedDigit(n, 9);
        int noise = rnd.next(0, max(1, n / 4));
        for (int i = 0; i < noise; ++i) {
            current[rnd.next(0, n - 1)] = char('0' + rnd.next(0, 9));
            target[rnd.next(0, n - 1)] = char('0' + rnd.next(0, 9));
        }
    }

    println(n);
    println(current);
    println(target);
    return 0;
}
