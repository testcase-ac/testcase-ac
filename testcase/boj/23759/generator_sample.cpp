#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomString(int k, int alphabetSize) {
    string s;
    for (int i = 0; i < k; ++i) {
        s += char('a' + rnd.next(alphabetSize));
    }
    return s;
}

string mutateShared(const string& base, int alphabetSize) {
    string s = base;
    int keep = rnd.next((int)s.size());
    for (int i = 0; i < (int)s.size(); ++i) {
        if (i == keep || rnd.next(3) == 0) continue;
        char c;
        do {
            c = char('a' + rnd.next(alphabetSize));
        } while (c == base[i] && alphabetSize > 1);
        s[i] = c;
    }
    return s;
}

string makeDisjoint(const string& prev, int alphabetSize) {
    string s = prev;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (alphabetSize == 1) continue;
        int shift = rnd.next(1, alphabetSize - 1);
        s[i] = char('a' + (prev[i] - 'a' + shift) % alphabetSize);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int k = rnd.next(1, 10);
    int n = rnd.next(1, 35);
    int alphabetSize = rnd.next(1, 26);

    vector<string> a;
    a.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a.push_back(randomString(k, alphabetSize));
    } else if (mode == 1) {
        string cur = randomString(k, alphabetSize);
        a.push_back(cur);
        for (int i = 1; i < n; ++i) {
            cur = mutateShared(cur, alphabetSize);
            a.push_back(cur);
        }
    } else if (mode == 2) {
        string cur = randomString(k, alphabetSize);
        a.push_back(cur);
        for (int i = 1; i < n; ++i) {
            cur = makeDisjoint(cur, alphabetSize);
            a.push_back(cur);
        }
    } else if (mode == 3) {
        int groups = rnd.next(1, 6);
        vector<string> base;
        for (int i = 0; i < groups; ++i) base.push_back(randomString(k, alphabetSize));
        for (int i = 0; i < n; ++i) {
            string s = rnd.any(base);
            if (rnd.next(2)) s = mutateShared(s, alphabetSize);
            a.push_back(s);
        }
    } else {
        int fixedPos = rnd.next(k);
        char fixedChar = char('a' + rnd.next(alphabetSize));
        for (int i = 0; i < n; ++i) {
            string s = randomString(k, alphabetSize);
            if (rnd.next(100) < 70) s[fixedPos] = fixedChar;
            a.push_back(s);
        }
    }

    println(n, k);
    for (const string& s : a) println(s);

    return 0;
}
