#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

char differentFrom(char c) {
    string choices = "RPS";
    choices.erase(remove(choices.begin(), choices.end(), c), choices.end());
    return choices[rnd.next(0, 1)];
}

char differentFromBoth(char a, char b) {
    string choices = "RPS";
    choices.erase(remove(choices.begin(), choices.end(), a), choices.end());
    choices.erase(remove(choices.begin(), choices.end(), b), choices.end());
    return choices.empty() ? differentFrom(a) : choices[0];
}

string makeRandomCase(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += string("RPS")[rnd.next(0, 2)];
    }
    return s;
}

string makeRunCase(int n) {
    string s;
    char c = string("RPS")[rnd.next(0, 2)];
    while ((int)s.size() < n) {
        int len = rnd.next(1, min(12, n - (int)s.size()));
        if (rnd.next(0, 4) == 0) {
            len = min(n - (int)s.size(), rnd.next(8, 24));
        }
        s.append(len, c);
        c = differentFrom(c);
    }
    return s;
}

string makeNoTieCase(int n) {
    string s;
    s.reserve(n);
    s += string("RPS")[rnd.next(0, 2)];
    for (int i = 1; i < n; ++i) {
        s += differentFrom(s.back());
    }
    if (s.front() == s.back()) {
        s.back() = differentFromBoth(s.front(), s[n - 2]);
    }
    return s;
}

string makeMostlyOneCase(int n) {
    char base = string("RPS")[rnd.next(0, 2)];
    string s(n, base);
    int changes = rnd.next(0, max(1, n / 4));
    for (int i = 0; i < changes; ++i) {
        s[rnd.next(0, n - 1)] = differentFrom(base);
    }
    return s;
}

string makeBoundaryTieCase(int n) {
    string s = makeNoTieCase(n);
    s.back() = s.front();
    if (n >= 4 && rnd.next(0, 1)) {
        int pos = rnd.next(1, n - 2);
        s[pos] = s[pos - 1];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 25);
    vector<string> cases;
    cases.reserve(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (rnd.next(0, 9) == 0) {
            n = rnd.next(80, 180);
        } else {
            n = rnd.next(3, 40);
        }

        if (mode == 0) {
            cases.push_back(makeRandomCase(n));
        } else if (mode == 1) {
            cases.push_back(makeRunCase(n));
        } else if (mode == 2) {
            cases.push_back(makeNoTieCase(n));
        } else if (mode == 3) {
            cases.push_back(makeMostlyOneCase(n));
        } else if (mode == 4) {
            cases.push_back(makeBoundaryTieCase(n));
        } else {
            char c = string("RPS")[rnd.next(0, 2)];
            cases.push_back(string(n, c));
        }
    }

    println(T);
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
