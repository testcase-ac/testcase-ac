#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    return s;
}

string makePalindrome(int n, const string& alphabet) {
    string s(n, 'a');
    for (int i = 0; i < (n + 1) / 2; ++i) {
        char c = rnd.any(alphabet);
        s[i] = c;
        s[n - 1 - i] = c;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> alphabets = {"ab", "abc", "abcd", "abcdefghijklmnopqrstuvwxyz"};
    string alphabet = rnd.any(alphabets);
    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 80);
        s = makePalindrome(n, alphabet);
    } else if (mode == 1) {
        int n = rnd.next(1, 120);
        s = randomString(n, alphabet);
    } else if (mode == 2) {
        int parts = rnd.next(2, 12);
        for (int i = 0; i < parts; ++i) {
            int len = rnd.next(1, 9);
            s += makePalindrome(len, alphabet);
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 120);
        char a = rnd.any(alphabet);
        char b = rnd.any(alphabet);
        while (alphabet.size() > 1 && b == a) b = rnd.any(alphabet);
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? a : b);
    } else if (mode == 4) {
        int blocks = rnd.next(1, 10);
        for (int i = 0; i < blocks; ++i) {
            char c = rnd.any(alphabet);
            int len = rnd.next(1, 15);
            s.append(len, c);
        }
    } else {
        int n = rnd.next(2, 100);
        s = randomString(n, alphabet);
        int edits = rnd.next(1, max(1, n / 8));
        for (int i = 0; i < edits; ++i) {
            int pos = rnd.next(0, n - 1);
            s[pos] = rnd.any(alphabet);
        }
        if (rnd.next(0, 1)) {
            string t = s;
            reverse(t.begin(), t.end());
            s += t.substr(rnd.next(0, (int)t.size() - 1));
        }
    }

    println(s);
    return 0;
}
