#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomWord(int n, char lo = 'a', char hi = 'z') {
    string result;
    result.reserve(n);
    for (int i = 0; i < n; ++i) {
        result.push_back(char('a' + rnd.next(lo - 'a', hi - 'a')));
    }
    return result;
}

string nextWord(string s) {
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        if (s[i] != 'z') {
            ++s[i];
            fill(s.begin() + i + 1, s.end(), 'a');
            return s;
        }
    }
    return s;
}

string previousWord(string s) {
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        if (s[i] != 'a') {
            --s[i];
            fill(s.begin() + i + 1, s.end(), 'z');
            return s;
        }
    }
    return s;
}

struct Case {
    int n;
    char required;
    string s;
    string t;
};

Case makeCase() {
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 24);
    char required = char('a' + rnd.next(0, 25));
    string s;
    string t;

    if (mode == 0) {
        n = rnd.next(1, 8);
        s = randomWord(n);
        while (s == string(n, 'z')) {
            s = randomWord(n);
        }
        t = nextWord(s);
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        s = randomWord(n, 'a', 'c');
        t = randomWord(n, 'x', 'z');
    } else if (mode == 2) {
        n = rnd.next(2, 24);
        int diff = rnd.next(0, n - 1);
        s = randomWord(n);
        s[diff] = char('a' + rnd.next(0, 24));
        for (int i = diff + 1; i < n; ++i) {
            s[i] = char('a' + rnd.next(0, 25));
        }
        t = s;
        t[diff] = char(s[diff] + rnd.next(1, 'z' - s[diff]));
        for (int i = diff + 1; i < n; ++i) {
            t[i] = char('a' + rnd.next(0, 25));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        string mid = randomWord(n);
        int pos = rnd.next(0, n - 1);
        mid[pos] = required;
        if (mid == string(n, 'a')) {
            mid[n - 1] = 'b';
        }
        if (mid == string(n, 'z')) {
            mid[n - 1] = 'y';
        }
        s = previousWord(mid);
        t = nextWord(mid);
    } else if (mode == 4) {
        n = rnd.next(2, 24);
        int prefix = rnd.next(0, n - 2);
        string common = randomWord(prefix);
        char left = char('a' + rnd.next(0, 23));
        char right = char(left + rnd.next(2, 'z' - left));
        s = common + left + randomWord(n - prefix - 1, 'x', 'z');
        t = common + right + randomWord(n - prefix - 1, 'a', 'c');
    } else {
        n = rnd.next(1, 24);
        do {
            s = randomWord(n);
            t = randomWord(n);
            if (t < s) {
                swap(s, t);
            }
        } while (s == t);
    }

    return {n, required, s, t};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int z = rnd.next(4, 10);
    vector<Case> cases;
    cases.reserve(z);
    int totalLength = 0;
    for (int i = 0; i < z; ++i) {
        Case tc = makeCase();
        totalLength += tc.n;
        cases.push_back(tc);
    }

    ensure(totalLength <= 100000);
    println(z);
    for (const Case& tc : cases) {
        println(tc.n, string(1, tc.required));
        println(tc.s);
        println(tc.t);
    }

    return 0;
}
