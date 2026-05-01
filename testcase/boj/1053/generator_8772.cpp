#include "testlib.h"
using namespace std;

string makePalindrome(int n, int alphaSize) {
    int halfLen = n / 2;
    string half;
    for (int i = 0; i < halfLen; ++i) {
        half += char('a' + rnd.next(0, alphaSize - 1));
    }
    string s = half;
    if (n % 2 == 1) {
        s += char('a' + rnd.next(0, alphaSize - 1));
    }
    for (int i = halfLen - 1; i >= 0; --i) {
        s += half[i];
    }
    return s;
}

bool isPalindrome(const string &s) {
    int n = (int)s.size();
    for (int i = 0; i < n / 2; ++i) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> samples = {
        "a", "aa", "ab", "ba", "aba", "abba",
        "abc", "acxcba", "abcacbd", "dabba", "babacvabba",
        "zzxyyx", "abcdedcba", "abcddcbae",
        "aaab", "baaa", "aabb", "aaabbb",
        "abcabc", "aaaaabbbbbccccc"
    };

    int pattern = rnd.next(1, 6);
    string s;

    if (pattern == 1) {
        // Hand-crafted sample
        s = rnd.any(samples);
    } else if (pattern == 2) {
        // Pure palindrome
        int n = rnd.next(1, 25);
        int alphaSize = rnd.next(2, 5);
        s = makePalindrome(n, alphaSize);
    } else if (pattern == 3) {
        // Near-palindrome with a few mismatches
        int n = rnd.next(2, 25);
        int alphaSize = rnd.next(3, 6);
        s = makePalindrome(n, alphaSize);

        int maxMism = max(1, min(n / 2, 3));
        int mism = rnd.next(1, maxMism);

        vector<int> pos;
        for (int i = 0; i < n / 2; ++i) pos.push_back(i);
        shuffle(pos.begin(), pos.end());
        pos.resize(mism);

        for (int idx : pos) {
            int j = n - 1 - idx;
            char orig = s[idx];
            char other;
            do {
                other = char('a' + rnd.next(0, alphaSize - 1));
            } while (other == orig || other == s[j]);
            s[idx] = other;
        }
    } else if (pattern == 4) {
        // Random string with all character counts even
        int alphaSize = rnd.next(1, 5);
        int halfLen = rnd.next(1, 12);
        string half;
        for (int i = 0; i < halfLen; ++i) {
            half += char('a' + rnd.next(0, alphaSize - 1));
        }
        s = half + half;
        shuffle(s.begin(), s.end());
    } else if (pattern == 5) {
        // General random string
        int n = rnd.next(1, 25);
        int alphaSize = rnd.next(2, 8);
        string alpha;
        for (int i = 0; i < alphaSize; ++i) alpha += char('a' + i);
        s.clear();
        for (int i = 0; i < n; ++i) {
            s += rnd.any(alpha);
        }
    } else if (pattern == 6) {
        // String that is exactly one swap away from a palindrome
        int attempts = 0;
        while (true) {
            int n = rnd.next(2, 25);
            int alphaSize = rnd.next(2, 6);
            s = makePalindrome(n, alphaSize);

            // Ensure not all characters equal
            bool allSame = true;
            for (int i = 1; i < n; ++i) {
                if (s[i] != s[0]) {
                    allSame = false;
                    break;
                }
            }
            if (allSame) {
                if (++attempts > 20) break; // fallback after many tries
                continue;
            }

            bool done = false;
            for (int tries = 0; tries < 50 && !done; ++tries) {
                int i = rnd.next(0, n - 1);
                int j = rnd.next(0, n - 1);
                if (i == j) continue;
                if (s[i] == s[j]) continue;
                swap(s[i], s[j]);
                if (!isPalindrome(s)) {
                    done = true;
                } else {
                    swap(s[i], s[j]);
                }
            }
            if (done) break;
            if (++attempts > 20) break;
        }
    }

    println(s);
    return 0;
}
