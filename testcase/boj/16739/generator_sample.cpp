#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

string randomLetters(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        if (rnd.next(2) == 0) {
            s += char('A' + rnd.next(26));
        } else {
            s += char('a' + rnd.next(26));
        }
    }
    return s;
}

string randomNumber(int maxLen) {
    int len = rnd.next(1, maxLen);
    string s(1, char('1' + rnd.next(9)));
    for (int i = 1; i < len; ++i) {
        s += char('0' + rnd.next(10));
    }
    return s;
}

string fitName(const vector<string>& parts) {
    string s;
    for (const string& part : parts) {
        if ((int)s.size() + (int)part.size() <= 9) {
            s += part;
        }
    }
    if (s.empty()) {
        return rnd.next(2) == 0 ? randomLetters(1) : randomNumber(1);
    }
    return s;
}

string randomName() {
    int target = rnd.next(1, 9);
    string s;
    bool lastDigit = false;
    while ((int)s.size() < target) {
        bool useDigit = s.empty() ? rnd.next(2) == 0 : rnd.next(3) != 0;
        int remaining = target - (int)s.size();
        if (useDigit) {
            int len = rnd.next(1, min(3, remaining));
            s += randomNumber(len);
            lastDigit = true;
        } else {
            s += randomLetters(1);
            lastDigit = false;
        }

        if (lastDigit && (int)s.size() < target && rnd.next(2) == 0) {
            s += randomLetters(1);
            lastDigit = false;
        }
    }
    return s;
}

string mutateAround(const string& base) {
    int mode = rnd.next(9);
    if (mode == 0) {
        return base;
    }
    if (mode == 1 && (int)base.size() < 9) {
        return base + (rnd.next(2) == 0 ? randomLetters(1) : randomNumber(1));
    }
    if (mode == 2 && (int)base.size() > 1) {
        return base.substr(0, rnd.next(1, (int)base.size() - 1));
    }
    if (mode == 3) {
        return randomNumber(rnd.next(1, 4)) + randomLetters(rnd.next(0, 2));
    }
    if (mode == 4) {
        return fitName({randomLetters(rnd.next(1, 3)), randomNumber(rnd.next(1, 4)),
                        randomLetters(rnd.next(0, 2))});
    }
    if (mode == 5) {
        return fitName({randomLetters(1), randomNumber(1), randomLetters(1),
                        randomNumber(1), randomLetters(rnd.next(0, 2))});
    }
    if (mode == 6) {
        string s = base;
        int pos = rnd.next((int)s.size());
        if (isdigit((unsigned char)s[pos])) {
            s[pos] = char('1' + rnd.next(9));
        } else if (isupper((unsigned char)s[pos])) {
            s[pos] = char('A' + rnd.next(26));
        } else {
            s[pos] = char('a' + rnd.next(26));
        }
        return s;
    }
    if (mode == 7) {
        int value = rnd.next(1, 300);
        return fitName({randomLetters(rnd.next(0, 2)), to_string(value),
                        randomLetters(rnd.next(0, 2))});
    }
    return randomName();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string base;
    int baseMode = rnd.next(5);
    if (baseMode == 0) {
        base = fitName({"file", to_string(rnd.next(1, 300))});
    } else if (baseMode == 1) {
        base = fitName({randomLetters(1), randomNumber(rnd.next(1, 3)),
                        randomLetters(rnd.next(0, 2))});
    } else if (baseMode == 2) {
        base = fitName({randomNumber(rnd.next(1, 3)), randomLetters(rnd.next(0, 3))});
    } else if (baseMode == 3) {
        base = randomLetters(rnd.next(1, 4));
    } else {
        base = randomName();
    }

    int n = rnd.next(1, 35);
    vector<string> names;
    names.push_back(base);
    for (int i = 0; i < n; ++i) {
        names.push_back(mutateAround(base));
    }

    println(n);
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
