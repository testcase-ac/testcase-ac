#include "testlib.h"
using namespace std;

string mutateOnce(const string &base) {
    string s = base;
    if (s.empty()) return string(1, rnd.any(string("()?*")));
    int action = rnd.next(0, 2); // 0: replace, 1: append, 2: keep
    if (action == 0) {
        int pos = rnd.next(0, (int)s.size() - 1);
        s[pos] = rnd.any(string("()?*"));
    } else if (action == 1 && (int)s.size() < 30) {
        s += rnd.any(string("()?*"));
    }
    return s;
}

string genRandomMix(int maxLen) {
    int n = rnd.next(1, maxLen);
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        int r = rnd.next(0, 99);
        if (r < 35) s += '(';
        else if (r < 70) s += ')';
        else if (r < 85) s += '?';
        else s += '*';
    }
    return s;
}

string genStarHeavy(int maxLen) {
    int n = rnd.next(1, maxLen);
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        int r = rnd.next(0, 99);
        if (r < 65) s += '*';
        else if (r < 75) s += '?';
        else if (r < 87) s += '(';
        else s += ')';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small T to keep output compact and generator very fast
    int T;
    if (argc > 1) {
        T = atoi(argv[1]);
        if (T < 1) T = 1;
        if (T > 10) T = 10;
    } else {
        T = rnd.next(4, 8);
    }

    // Predefined tricky and edge-case patterns
    vector<string> base = {
        "(", ")", "?", "*",
        "()", ")(", "()()", "(())", ")()(",
        "****", "????", "*?*", "?*?", "(*?)",
        "*)))(((*", "?()(?*))(()?", "()??))", "())*(())"
    };

    println(T);
    for (int i = 0; i < T; ++i) {
        string s;
        int tp;
        if (i < 3) {
            // Ensure we include some predefined tricky ones
            s = mutateOnce(base[i % (int)base.size()]);
        } else {
            tp = rnd.next(0, 2); // 0: from base, 1: random mix, 2: star-heavy
            if (tp == 0) {
                s = mutateOnce(rnd.any(base));
            } else if (tp == 1) {
                s = genRandomMix(25);
            } else {
                s = genStarHeavy(25);
            }
        }

        if (s.empty()) s = "*";
        if ((int)s.size() > 30) s.resize(30);
        println(s);
    }

    return 0;
}
