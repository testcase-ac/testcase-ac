#include "testlib.h"

#include <string>

using namespace std;

char randomDigit(int low = 1, int high = 9) {
    return char('0' + rnd.next(low, high));
}

string randomString(int n, int low = 1, int high = 9) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomDigit(low, high));
    }
    return s;
}

string palindromeString(int n) {
    string s(n, '1');
    for (int i = 0; i < (n + 1) / 2; ++i) {
        s[i] = s[n - 1 - i] = randomDigit();
    }
    return s;
}

string mirroredMismatchString(int n) {
    string s = randomString(n);
    for (int i = 0; i < n / 2; ++i) {
        int left = rnd.next(1, 9);
        int right = rnd.next(1, 9);
        if (rnd.next(0, 3) != 0) {
            while (right == left) {
                right = rnd.next(1, 9);
            }
        }
        s[i] = char('0' + left);
        s[n - 1 - i] = char('0' + right);
    }
    return s;
}

string heavyDigitString(int n) {
    char major = randomDigit();
    char minor = randomDigit();
    while (minor == major) {
        minor = randomDigit();
    }

    string s(n, major);
    int changes = rnd.next(1, n);
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(0, n - 1);
        s[pos] = rnd.next(0, 4) == 0 ? randomDigit() : minor;
    }
    return s;
}

string ascendingBlocks(int n) {
    string s;
    s.reserve(n);
    int digit = rnd.next(1, 9);
    while ((int)s.size() < n) {
        int len = rnd.next(1, 5);
        for (int i = 0; i < len && (int)s.size() < n; ++i) {
            s.push_back(char('0' + digit));
        }
        digit += rnd.next(1, 3);
        if (digit > 9) {
            digit = rnd.next(1, 3);
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 5) {
        n = rnd.next(80, 400);
    } else {
        n = rnd.next(7, 35);
    }

    string a;
    if (mode == 0) {
        a = randomString(n);
    } else if (mode == 1) {
        a = palindromeString(n);
    } else if (mode == 2) {
        a = mirroredMismatchString(n);
    } else if (mode == 3) {
        a = heavyDigitString(n);
    } else if (mode == 4) {
        a = ascendingBlocks(n);
    } else {
        int low = rnd.next(1, 6);
        int high = rnd.next(low, 9);
        a = randomString(n, low, high);
    }

    println(n);
    println(a);
    return 0;
}
