#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomDigits(int len) {
    string s;
    s.reserve(len);
    s.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(10)));
    }
    return s;
}

string palindrome(int len) {
    string s(len, '0');
    for (int i = 0; i < (len + 1) / 2; ++i) {
        int lo = (i == 0) ? 1 : 0;
        char d = char('0' + rnd.next(lo, 9));
        s[i] = d;
        s[len - 1 - i] = d;
    }
    return s;
}

string powerOfTenLike(int len) {
    string s(len, '0');
    s[0] = '1';
    if (len > 1 && rnd.next(2) == 1) {
        int pos = rnd.next(1, len - 1);
        s[pos] = char('1' + rnd.next(9));
    }
    return s;
}

string mostlyNines(int len) {
    string s(len, '9');
    int changes = rnd.next(1, max(1, min(len, 4)));
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(len);
        int lo = (pos == 0) ? 1 : 0;
        s[pos] = char('0' + rnd.next(lo, 8));
    }
    return s;
}

string nearPalindrome(int len) {
    string s = palindrome(len);
    int changes = rnd.next(1, max(1, min(len, 3)));
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(len);
        int lo = (pos == 0) ? 1 : 0;
        char d;
        do {
            d = char('0' + rnd.next(lo, 9));
        } while (d == s[pos]);
        s[pos] = d;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(6, 18);
    vector<string> numbers;
    numbers.reserve(z);

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(6);
        int len;
        if (tc < 2) {
            len = rnd.next(1, 5);
        } else if (rnd.next(100) < 75) {
            len = rnd.next(1, 30);
        } else {
            len = rnd.next(31, 120);
        }

        if (mode == 0) {
            numbers.push_back(randomDigits(len));
        } else if (mode == 1) {
            numbers.push_back(palindrome(len));
        } else if (mode == 2) {
            numbers.push_back(powerOfTenLike(len));
        } else if (mode == 3) {
            numbers.push_back(mostlyNines(len));
        } else if (mode == 4) {
            numbers.push_back(nearPalindrome(len));
        } else {
            string s = randomDigits(len);
            int suffixZeros = min(len - 1, rnd.next(0, min(len, 8)));
            for (int i = 0; i < suffixZeros; ++i) {
                s[len - 1 - i] = '0';
            }
            numbers.push_back(s);
        }
    }

    shuffle(numbers.begin(), numbers.end());

    println(static_cast<int>(numbers.size()));
    for (const string& n : numbers) {
        println(n);
    }

    return 0;
}
