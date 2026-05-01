#include "testlib.h"
using namespace std;

bool isVowel(char c) {
    return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
}

bool hasVowel(const string &s) {
    for (char c : s) if (isVowel(c)) return true;
    return false;
}

bool hasTriple(const string &s) {
    int cv = 0, cc = 0;
    for (char c : s) {
        if (isVowel(c)) {
            cv++;
            cc = 0;
        } else {
            cc++;
            cv = 0;
        }
        if (cv >= 3 || cc >= 3) return true;
    }
    return false;
}

bool hasBadDouble(const string &s) {
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i] == s[i-1] && !(s[i] == 'e' || s[i] == 'o'))
            return true;
    }
    return false;
}

bool isAcceptable(const string &s) {
    if (!hasVowel(s)) return false;
    if (hasTriple(s)) return false;
    if (hasBadDouble(s)) return false;
    return true;
}

string genAcceptable(int minLen, int maxLen) {
    while (true) {
        int len = rnd.next(minLen, maxLen);
        string s;
        s.reserve(len);
        int cv = 0, cc = 0;
        for (int i = 0; i < len; ++i) {
            vector<char> cand;
            for (char c = 'a'; c <= 'z'; ++c) {
                bool v = isVowel(c);
                if (i > 0 && c == s[i-1] && !(c == 'e' || c == 'o'))
                    continue;
                int nv = v ? cv + 1 : 0;
                int nc = v ? 0 : cc + 1;
                if (nv >= 3 || nc >= 3)
                    continue;
                cand.push_back(c);
            }
            char c = rnd.any(cand);
            s.push_back(c);
            if (isVowel(c)) {
                cv++;
                cc = 0;
            } else {
                cc++;
                cv = 0;
            }
        }
        if (isAcceptable(s)) return s;
    }
}

string genNoVowel() {
    const string cons = "bcdfghjklmnpqrstvwxyz";
    if (rnd.next(0, 1) == 0) {
        // short, avoid doubles
        int len = rnd.next(1, 2);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; ++i) {
            char c;
            while (true) {
                c = rnd.any(cons);
                if (i == 0 || c != s[i-1]) break;
            }
            s.push_back(c);
        }
        return s;
    } else {
        int len = rnd.next(3, 15);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; ++i) {
            s.push_back(rnd.any(cons));
        }
        return s;
    }
}

string genBadTripleVowel() {
    string vowels = "aeiou";
    string s = genAcceptable(3, 20);
    int n = (int)s.size();
    int pos = rnd.next(0, n - 3);
    char v = rnd.any(vowels);
    s[pos] = s[pos+1] = s[pos+2] = v;
    return s;
}

string genBadTripleConsonant() {
    while (true) {
        string s = genAcceptable(3, 20);
        int n = (int)s.size();
        int pos = rnd.next(0, n - 3);
        char c;
        do {
            c = char('a' + rnd.next(0, 25));
        } while (isVowel(c));
        s[pos] = s[pos+1] = s[pos+2] = c;
        if (hasVowel(s)) return s;
    }
}

string genBadDouble() {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        string s = genAcceptable(2, 20);
        int n = (int)s.size();
        vector<int> idx;
        for (int i = 0; i < n - 1; ++i) idx.push_back(i);
        shuffle(idx.begin(), idx.end());
        for (int i : idx) {
            for (int tries = 0; tries < 5; ++tries) {
                char c = char('a' + rnd.next(0, 25));
                if (c == 'e' || c == 'o') continue;
                string t = s;
                t[i] = t[i+1] = c;
                if (hasVowel(t) && !hasTriple(t) && hasBadDouble(t))
                    return t;
            }
        }
    }
    // Fallback simple clearly bad double (also no vowel)
    return "bb";
}

string genRandomString() {
    int len = rnd.next(1, 20);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('a' + rnd.next(0, 25)));
    }
    return s;
}

void fixIfEnd(string &s) {
    if (s == "end") {
        s[0] = (s[0] == 'a' ? 'b' : 'a');
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> tests;

    // Always include sample-like interesting cases
    vector<string> base = {
        "a", "tv", "ptoui", "bontres", "zoggax", "wiinq", "eep", "houctuh"
    };
    for (string s : base) {
        fixIfEnd(s);
        tests.push_back(s);
    }

    int extra = rnd.next(2, 10);
    for (int i = 0; i < extra; ++i) {
        int type = rnd.next(0, 4);
        // Occasionally just a fully random string
        if (rnd.next(0, 9) == 0) type = 5;

        string s;
        if (type == 0) {
            s = genAcceptable(1, 20);
        } else if (type == 1) {
            s = genNoVowel();
        } else if (type == 2) {
            s = genBadTripleVowel();
        } else if (type == 3) {
            s = genBadTripleConsonant();
        } else if (type == 4) {
            s = genBadDouble();
        } else {
            s = genRandomString();
        }

        fixIfEnd(s);
        tests.push_back(s);
    }

    // Shuffle test cases for variety
    shuffle(tests.begin(), tests.end());

    for (const string &s : tests)
        println(s);
    println("end");

    return 0;
}
