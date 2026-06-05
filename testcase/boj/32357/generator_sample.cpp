#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomString(int len, int alphabetSize) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('a' + rnd.next(alphabetSize)));
    }
    return s;
}

string palindromeString(int halfLen, int alphabetSize) {
    string left = randomString(halfLen, alphabetSize);
    string s = left;
    reverse(left.begin(), left.end());
    s += left;
    return s;
}

bool isPalindrome(const string& s) {
    for (int i = 0, j = int(s.size()) - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) return false;
    }
    return true;
}

void addUnique(vector<string>& strings, set<string>& seen, const string& candidate) {
    if (seen.insert(candidate).second) {
        strings.push_back(candidate);
    }
}

string nonPalindromeString(int halfLen, int alphabetSize) {
    while (true) {
        string s = randomString(2 * halfLen, alphabetSize);
        if (!isPalindrome(s)) return s;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 18);
    int alphabetSize = rnd.next(2, 8);
    int maxHalfLen = rnd.next(4, 12);

    vector<string> strings;
    set<string> seen;

    if (mode == 0) {
        int palCount = rnd.next(2, n);
        while (int(strings.size()) < palCount) {
            addUnique(strings, seen, palindromeString(rnd.next(1, maxHalfLen), alphabetSize));
        }
    } else if (mode == 1) {
        while (int(strings.size()) < n / 2) {
            int halfLen = rnd.next(1, maxHalfLen);
            string s = randomString(2 * halfLen, alphabetSize);
            addUnique(strings, seen, s);
            string reversed = s;
            reverse(reversed.begin(), reversed.end());
            addUnique(strings, seen, reversed);
        }
    } else if (mode == 2) {
        while (int(strings.size()) < n) {
            int halfLen = rnd.next(1, maxHalfLen);
            string left = randomString(halfLen, alphabetSize);
            string right = randomString(halfLen, alphabetSize);
            string s = left + right;
            if (rnd.next(2) == 0) {
                reverse(right.begin(), right.end());
                s = left + right;
            }
            addUnique(strings, seen, s);
        }
    } else if (mode == 3) {
        while (int(strings.size()) < n) {
            int halfLen = rnd.next(1, maxHalfLen);
            addUnique(strings, seen, randomString(2 * halfLen, alphabetSize));
        }
    } else {
        while (int(strings.size()) < n) {
            int halfLen = rnd.next(1, maxHalfLen);
            if (rnd.next(3) == 0) {
                addUnique(strings, seen, palindromeString(halfLen, alphabetSize));
            } else {
                addUnique(strings, seen, nonPalindromeString(halfLen, alphabetSize));
            }
        }
    }

    while (int(strings.size()) < n) {
        int halfLen = rnd.next(1, maxHalfLen);
        addUnique(strings, seen, nonPalindromeString(halfLen, alphabetSize));
    }

    shuffle(strings.begin(), strings.end());

    println(int(strings.size()));
    for (const string& s : strings) {
        println(s);
    }

    return 0;
}
