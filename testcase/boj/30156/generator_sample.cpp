#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string repeatedString(int n, char c) {
    return string(n, c);
}

string randomString(int n, int aWeight) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next(1, 100) <= aWeight ? 'a' : 'b');
    }
    return s;
}

string alternatingRuns(int n) {
    string s;
    s.reserve(n);

    char c = rnd.next(0, 1) == 0 ? 'a' : 'b';
    while ((int)s.size() < n) {
        int run = rnd.next(1, 5);
        for (int i = 0; i < run && (int)s.size() < n; ++i) {
            s.push_back(c);
        }
        c = c == 'a' ? 'b' : 'a';
    }

    return s;
}

string balancedString(int n) {
    string s;
    s.reserve(n);

    int aCount = n / 2;
    if (n % 2 == 1 && rnd.next(0, 1) == 1) {
        ++aCount;
    }

    for (int i = 0; i < aCount; ++i) {
        s.push_back('a');
    }
    while ((int)s.size() < n) {
        s.push_back('b');
    }
    shuffle(s.begin(), s.end());

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 25);
    vector<string> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 30);

        if (mode == 0) {
            cases.push_back(repeatedString(n, rnd.next(0, 1) == 0 ? 'a' : 'b'));
        } else if (mode == 1) {
            cases.push_back(randomString(n, rnd.next(10, 90)));
        } else if (mode == 2) {
            cases.push_back(balancedString(n));
        } else if (mode == 3) {
            cases.push_back(alternatingRuns(n));
        } else if (mode == 4) {
            int majority = rnd.next(n / 2 + 1, n);
            string s(majority, rnd.next(0, 1) == 0 ? 'a' : 'b');
            char other = s[0] == 'a' ? 'b' : 'a';
            s += string(n - majority, other);
            shuffle(s.begin(), s.end());
            cases.push_back(s);
        } else {
            cases.push_back(randomString(rnd.next(1, 100), rnd.next(1, 99)));
        }
    }

    println((int)cases.size());
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
