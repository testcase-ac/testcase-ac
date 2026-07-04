#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomLetters(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string palindromeFromHalf(int halfLen, bool odd, const string& alphabet) {
    string left = randomLetters(halfLen, alphabet);
    string right = left;
    reverse(right.begin(), right.end());
    if (odd) {
        return left + rnd.any(alphabet) + right;
    }
    return left + right;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> alphabets = {"A", "AB", "ABC", "ABCDE", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const string alphabet = rnd.any(alphabets);
    const int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = randomLetters(rnd.next(1, 28), alphabet);
    } else if (mode == 1) {
        int n = rnd.next(1, 30);
        char c = rnd.any(alphabet);
        s.assign(n, c);
    } else if (mode == 2) {
        int halfLen = rnd.next(0, 14);
        bool odd = rnd.next(0, 1) == 1;
        s = palindromeFromHalf(halfLen, odd, alphabet);
        if (s.empty()) {
            s += rnd.any(alphabet);
        }
    } else if (mode == 3) {
        int pieces = rnd.next(2, 8);
        for (int i = 0; i < pieces; ++i) {
            int halfLen = rnd.next(0, 3);
            bool odd = rnd.next(0, 1) == 1;
            string piece = palindromeFromHalf(halfLen, odd, alphabet);
            if (piece.empty()) {
                piece += rnd.any(alphabet);
            }
            s += piece;
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            s += char('A' + (i % 26));
        }
    } else {
        int blocks = rnd.next(2, 7);
        for (int i = 0; i < blocks; ++i) {
            char c = rnd.any(alphabet);
            s.append(rnd.next(1, 5), c);
        }
    }

    println(s);
    return 0;
}
