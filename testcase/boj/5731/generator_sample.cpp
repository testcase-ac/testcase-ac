#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const string HEX = "0123456789ABCDEF";

string randomHexWord(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string word;
    for (int i = 0; i < len; ++i) {
        word += rnd.any(HEX);
    }
    return word;
}

void addUnique(set<string>& used, const string& word) {
    if (!word.empty() && word.size() <= 50) {
        used.insert(word);
    }
}

vector<string> makePrefixCase() {
    set<string> used;
    string a(1, rnd.any(HEX));
    string b(1, rnd.any(HEX));
    while (b == a) {
        b = string(1, rnd.any(HEX));
    }

    addUnique(used, a);
    addUnique(used, a + b);
    addUnique(used, b + a);
    addUnique(used, a + b + a);

    int extra = rnd.next(0, 4);
    while ((int)used.size() < 4 + extra) {
        addUnique(used, randomHexWord(1, 6));
    }

    return vector<string>(used.begin(), used.end());
}

vector<string> makeFixedLengthCase() {
    set<string> used;
    int len = rnd.next(1, 5);
    int n = rnd.next(2, 10);
    while ((int)used.size() < n) {
        addUnique(used, randomHexWord(len, len));
    }
    return vector<string>(used.begin(), used.end());
}

vector<string> makeOverlapCase() {
    set<string> used;
    string a(1, rnd.any(HEX));
    string b(1, rnd.any(HEX));
    string c(1, rnd.any(HEX));
    while (b == a) {
        b = string(1, rnd.any(HEX));
    }
    while (c == a || c == b) {
        c = string(1, rnd.any(HEX));
    }

    addUnique(used, a + b);
    addUnique(used, b + c);
    addUnique(used, a + b + c);
    addUnique(used, c + a);
    addUnique(used, a + c + b);

    int extra = rnd.next(0, 5);
    while ((int)used.size() < 5 + extra) {
        addUnique(used, randomHexWord(2, 8));
    }

    return vector<string>(used.begin(), used.end());
}

vector<string> makeSingletonCase() {
    return vector<string>{randomHexWord(rnd.next(1, 10), rnd.next(10, 50))};
}

vector<string> makeMixedCase() {
    set<string> used;
    int n = rnd.next(6, 18);
    string base = randomHexWord(2, 6);
    addUnique(used, base);
    addUnique(used, base + randomHexWord(1, 4));

    while ((int)used.size() < n) {
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            addUnique(used, randomHexWord(1, 4));
        } else if (mode == 1) {
            addUnique(used, base.substr(0, rnd.next(1, (int)base.size())) + randomHexWord(1, 5));
        } else {
            addUnique(used, randomHexWord(8, 20));
        }
    }

    return vector<string>(used.begin(), used.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<string>> cases;
    cases.push_back(makePrefixCase());
    cases.push_back(makeFixedLengthCase());
    cases.push_back(makeOverlapCase());

    int extraCases = rnd.next(1, 4);
    for (int i = 0; i < extraCases; ++i) {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            cases.push_back(makeSingletonCase());
        } else if (mode == 1) {
            cases.push_back(makeFixedLengthCase());
        } else {
            cases.push_back(makeMixedCase());
        }
    }

    shuffle(cases.begin(), cases.end());

    for (const vector<string>& words : cases) {
        cout << words.size() << '\n';
        vector<string> shuffled = words;
        shuffle(shuffled.begin(), shuffled.end());
        for (const string& word : shuffled) {
            cout << word << '\n';
        }
    }
    cout << 0 << '\n';

    return 0;
}
