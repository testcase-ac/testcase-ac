#include "testlib.h"
using namespace std;

bool isPalindrome(const string &s) {
    int n = (int)s.size();
    for (int i = 0; i < n / 2; ++i)
        if (s[i] != s[n - 1 - i]) return false;
    return true;
}

bool allSame(const string &s) {
    for (int i = 1; i < (int)s.size(); ++i)
        if (s[i] != s[0]) return false;
    return true;
}

string randomString(int n, char maxCh = 'D') {
    string s(n, 'A');
    for (int i = 0; i < n; ++i)
        s[i] = (char)('A' + rnd.next(0, maxCh - 'A'));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a pattern type for diversity
    int pattern = rnd.next(0, 8);
    string s;

    switch (pattern) {
        case 0: {
            // Length 1 (always palindrome, all same)
            int n = 1;
            s = randomString(n, 'C');
            break;
        }
        case 1: {
            // Length 2 palindrome, all same
            char ch = (char)('A' + rnd.next(0, 2));
            s = string(2, ch);
            break;
        }
        case 2: {
            // Length 2 non-palindrome
            char a = (char)('A' + rnd.next(0, 2));
            char b = a;
            while (b == a) b = (char)('A' + rnd.next(0, 2));
            s = string(1, a) + string(1, b);
            break;
        }
        case 3: {
            // All same, length 3~20
            int n = rnd.next(3, 20);
            char ch = (char)('A' + rnd.next(0, 3));
            s = string(n, ch);
            break;
        }
        case 4: {
            // Palindrome with at least two different characters, length 3~30
            int n = rnd.next(3, 30);
            s.assign(n, 'A');
            for (int i = 0; i < n / 2; ++i) {
                char c = (char)('A' + rnd.next(0, 3));
                s[i] = s[n - 1 - i] = c;
            }
            if (n % 2 == 1) {
                s[n / 2] = (char)('A' + rnd.next(0, 3));
            }
            if (allSame(s)) {
                // Change a symmetric pair to another char to keep palindrome but not all same
                char old = s[0];
                char neu = old;
                while (neu == old) neu = (char)('A' + rnd.next(0, 3));
                s[0] = s[n - 1] = neu;
            }
            break;
        }
        case 5: {
            // Random non-palindrome, length 3~30
            int n = rnd.next(3, 30);
            s = randomString(n);
            if (isPalindrome(s)) {
                int pos = rnd.next(0, n - 1);
                char old = s[pos];
                char neu = old;
                while (neu == old) neu = (char)('A' + rnd.next(0, 3));
                s[pos] = neu;
            }
            break;
        }
        case 6: {
            // Medium-length palindrome (60~120) with multiple chars
            int n = rnd.next(60, 120);
            s.assign(n, 'A');
            for (int i = 0; i < n / 2; ++i) {
                char c = (char)('A' + rnd.next(0, 4));
                s[i] = s[n - 1 - i] = c;
            }
            if (n % 2 == 1) {
                s[n / 2] = (char)('A' + rnd.next(0, 4));
            }
            if (allSame(s)) {
                char old = s[0];
                char neu = old;
                while (neu == old) neu = (char)('A' + rnd.next(0, 4));
                s[0] = s[n - 1] = neu;
            }
            break;
        }
        case 7: {
            // Almost all same: "AAAA...A B" (non-palindrome, long uniform prefix)
            int n = rnd.next(3, 25);
            char base = (char)('A' + rnd.next(0, 2));
            char diff = base;
            while (diff == base) diff = (char)('A' + rnd.next(0, 2));
            s = string(n, base);
            s[n - 1] = diff;
            break;
        }
        case 8: {
            // Medium-length random non-palindrome (60~120)
            int n = rnd.next(60, 120);
            s = randomString(n, 'Z');
            if (isPalindrome(s)) {
                int pos = rnd.next(0, n - 1);
                char old = s[pos];
                char neu = old;
                while (neu == old) neu = (char)('A' + rnd.next(0, 25));
                s[pos] = neu;
            }
            break;
        }
    }

    println(s);
    return 0;
}
