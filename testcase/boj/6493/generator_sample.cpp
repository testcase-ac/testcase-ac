#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string makeSlump(int depth) {
    char first = rnd.any(string("DE"));
    int fCount = rnd.next(1, max(1, 5 - depth));
    string s(1, first);
    s += string(fCount, 'F');

    if (depth >= 3 || rnd.next(2) == 0) {
        s += 'G';
    } else {
        s += makeSlump(depth + 1);
    }
    return s;
}

string makeSlimp(int depth) {
    if (depth >= 4 || rnd.next(4) == 0) {
        return "AH";
    }

    if (rnd.next(2) == 0) {
        return "AB" + makeSlimp(depth + 1) + "C";
    }
    return "A" + makeSlump(0) + "C";
}

string makeSlurpy() {
    return makeSlimp(0) + makeSlump(0);
}

string randomAlpha() {
    static const string letters =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int len = rnd.next(1, 30);
    string s;
    for (int i = 0; i < len; ++i) {
        s += rnd.any(letters);
    }
    return s;
}

string mutate(string s) {
    static const string letters =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int mode = rnd.next(5);

    if (mode == 0 && s.size() < 60) {
        s.insert(s.begin() + rnd.next(0, int(s.size())), rnd.any(letters));
    } else if (mode == 1 && s.size() > 1) {
        s.erase(s.begin() + rnd.next(0, int(s.size()) - 1));
    } else if (mode == 2) {
        s[rnd.next(0, int(s.size()) - 1)] = rnd.any(letters);
    } else if (mode == 3) {
        reverse(s.begin(), s.end());
    } else {
        s += rnd.any(string("ABCDFGH"));
    }

    if (s.size() > 60) {
        s.resize(60);
    }
    return s.empty() ? "A" : s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    vector<string> tests;

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(6);
        string s;

        if (mode <= 2) {
            s = makeSlurpy();
        } else if (mode == 3) {
            s = makeSlimp(0);
        } else if (mode == 4) {
            s = makeSlump(0);
        } else if (rnd.next(2) == 0) {
            s = mutate(makeSlurpy());
        } else {
            s = randomAlpha();
        }

        if (s.size() > 60) {
            s.resize(60);
        }
        tests.push_back(s);
    }

    println(n);
    for (const string& s : tests) {
        println(s);
    }

    return 0;
}
