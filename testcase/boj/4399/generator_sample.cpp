#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(alphabet[rnd.next(static_cast<int>(alphabet.size()))]);
    }
    return s;
}

string palindrome(int len, const string& alphabet) {
    string s(len, 'a');
    for (int i = 0; i < (len + 1) / 2; ++i) {
        char c = alphabet[rnd.next(static_cast<int>(alphabet.size()))];
        s[i] = c;
        s[len - 1 - i] = c;
    }
    return s;
}

string mutateOne(string s, const string& alphabet) {
    if (s.empty()) return string(1, alphabet[rnd.next(static_cast<int>(alphabet.size()))]);

    int pos = rnd.next(static_cast<int>(s.size()));
    char c = alphabet[rnd.next(static_cast<int>(alphabet.size()))];
    if (alphabet.size() > 1) {
        while (c == s[pos]) c = alphabet[rnd.next(static_cast<int>(alphabet.size()))];
    }
    s[pos] = c;
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<string, string>> cases;
    int targetCases = rnd.next(18, 45);
    int totalLength = 0;

    auto addCase = [&](string a, string b) {
        if (totalLength + static_cast<int>(a.size() + b.size()) > 700) return;
        cases.push_back({a, b});
        totalLength += static_cast<int>(a.size() + b.size());
    };

    addCase("", "");
    addCase("", randomString(rnd.next(1, 8), "ab"));
    addCase(randomString(rnd.next(1, 8), "abc"), "");

    while (static_cast<int>(cases.size()) < targetCases) {
        string alphabet = "ab";
        if (rnd.next(100) < 45) alphabet = "abc";
        if (rnd.next(100) < 15) alphabet = "abcd";

        int mode = rnd.next(8);
        int lenA = rnd.next(0, 24);
        int lenB = rnd.next(0, 24);
        string a, b;

        if (mode == 0) {
            a = randomString(lenA, alphabet);
            b = a;
        } else if (mode == 1) {
            a = palindrome(lenA, alphabet);
            b = palindrome(lenB, alphabet);
        } else if (mode == 2) {
            a = palindrome(lenA, alphabet);
            b = mutateOne(a, alphabet);
        } else if (mode == 3) {
            string base = randomString(rnd.next(1, 12), alphabet);
            a = base + randomString(rnd.next(0, 8), alphabet);
            b = base + randomString(rnd.next(0, 8), alphabet);
        } else if (mode == 4) {
            string tail = randomString(rnd.next(1, 12), alphabet);
            a = randomString(rnd.next(0, 8), alphabet) + tail;
            b = randomString(rnd.next(0, 8), alphabet) + tail;
        } else if (mode == 5) {
            a = randomString(lenA, string(1, alphabet[0]));
            b = randomString(lenB, alphabet);
        } else if (mode == 6) {
            a = randomString(lenA, alphabet);
            b = a;
            reverse(b.begin(), b.end());
        } else {
            a = randomString(lenA, alphabet);
            b = randomString(lenB, alphabet);
        }

        addCase(a, b);
    }

    if (cases.back().second.empty()) {
        cases.back().second = randomString(rnd.next(1, 8), "ab");
    }

    ensure(!cases.empty());
    for (const auto& tc : cases) {
        cout << tc.first << '\n' << tc.second << '\n';
    }

    return 0;
}
