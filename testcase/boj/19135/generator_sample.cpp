#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int len, double bProb) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.next() < bProb ? 'b' : 'a');
    }
    return s;
}

string expandOnce(const string& s) {
    string out;
    out.reserve(s.size() * 2);
    for (char c : s) {
        if (c == 'a') {
            out += "aa";
        } else {
            out += "ab";
        }
    }
    return out;
}

string expandTimes(string s, int k) {
    for (int i = 0; i < k; ++i) {
        s = expandOnce(s);
    }
    return s;
}

string substringOf(const string& s, int minLen, int maxLen) {
    int len = rnd.next(minLen, min<int>(maxLen, s.size()));
    int start = rnd.next(0, static_cast<int>(s.size()) - len);
    return s.substr(start, len);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s, t;

    if (mode == 0) {
        int sLen = rnd.next(1, 30);
        int tLen = rnd.next(1, 30);
        double bProb = rnd.next(0.05, 0.95);
        s = randomString(sLen, bProb);
        t = randomString(tLen, rnd.next(0.05, 0.95));
    } else if (mode == 1) {
        int sLen = rnd.next(1, 35);
        s = randomString(sLen, rnd.next(0.15, 0.85));
        t = substringOf(s, 1, min(20, sLen));
    } else if (mode == 2) {
        int sLen = rnd.next(1, 12);
        int k = rnd.next(1, 5);
        s = randomString(sLen, rnd.next(0.15, 0.85));
        string expanded = expandTimes(s, k);
        t = substringOf(expanded, 1, min<int>(40, expanded.size()));
    } else if (mode == 3) {
        s = string(rnd.next(1, 25), 'a');
        int tLen = rnd.next(1, 25);
        t = randomString(tLen, rnd.next(0.20, 0.80));
        t[rnd.next(0, tLen - 1)] = 'b';
    } else if (mode == 4) {
        int sLen = rnd.next(1, 20);
        s.reserve(sLen);
        char cur = rnd.next(0, 1) ? 'a' : 'b';
        for (int i = 0; i < sLen; ++i) {
            if (rnd.next() < 0.75) cur = (cur == 'a' ? 'b' : 'a');
            s.push_back(cur);
        }

        string expanded = expandTimes(s, rnd.next(1, 4));
        int tLen = rnd.next(1, min<int>(45, expanded.size()));
        int start = rnd.next(0, static_cast<int>(expanded.size()) - tLen);
        t = expanded.substr(start, tLen);
        if (rnd.next(0, 2) == 0) {
            t[rnd.next(0, tLen - 1)] = rnd.next(0, 1) ? 'a' : 'b';
        }
    } else {
        vector<string> patterns = {
            "a", "b", "ab", "ba", "aaab", "abab", "baba", "abba"
        };
        s = rnd.any(patterns);
        int repeats = rnd.next(1, 4);
        string base;
        for (int i = 0; i < repeats; ++i) {
            base += rnd.any(patterns);
        }
        t = base.substr(0, rnd.next(1, min<int>(base.size(), 30)));
    }

    println(s);
    println(t);
    return 0;
}
