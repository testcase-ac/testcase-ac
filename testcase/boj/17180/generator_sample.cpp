#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomString(int len, const string& alphabet) {
    string result;
    result.reserve(len);
    for (int i = 0; i < len; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

string stretchString(const string& base, int targetLen) {
    vector<int> copies(base.size(), 1);
    for (int i = (int)base.size(); i < targetLen; ++i) {
        ++copies[rnd.next((int)base.size())];
    }

    string result;
    result.reserve(targetLen);
    for (int i = 0; i < (int)base.size(); ++i) {
        result.append(copies[i], base[i]);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;
    string s;
    string t;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
        s = randomString(n, "az");
        t = randomString(m, "az");
    } else if (mode == 1) {
        int baseLen = rnd.next(1, 8);
        string alphabet = rnd.next(0, 1) == 0 ? "abc" : "mnop";
        string base = randomString(baseLen, alphabet);
        n = rnd.next(baseLen, 25);
        m = rnd.next(baseLen, 25);
        s = stretchString(base, n);
        t = stretchString(base, m);
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        m = rnd.next(1, 30);
        string alphabet = rnd.next(0, 1) == 0 ? "abcde" : "vwxyz";
        s = randomString(n, alphabet);
        t = randomString(m, alphabet);
    } else if (mode == 3) {
        n = rnd.next(20, 45);
        m = rnd.next(1, 6);
        if (rnd.next(0, 1) == 0) {
            swap(n, m);
        }
        s = randomString(n, "abcdefghijklmnopqrstuvwxyz");
        t = randomString(m, "abcdefghijklmnopqrstuvwxyz");
    } else if (mode == 4) {
        n = rnd.next(10, 60);
        m = rnd.next(10, 60);
        s = randomString(n, "aaaabbbbccccxyz");
        t = randomString(m, "abcxxxxyyyyzzzz");
    } else {
        n = rnd.next(1, 300);
        m = rnd.next(1, 300);
        char left = rnd.next(0, 1) == 0 ? 'a' : 'z';
        char right = left == 'a' ? 'z' : 'a';
        s.assign(n, left);
        t.assign(m, right);
        if (rnd.next(0, 2) == 0) {
            s[rnd.next(n)] = (char)rnd.next('a', 'z');
        }
        if (rnd.next(0, 2) == 0) {
            t[rnd.next(m)] = (char)rnd.next('a', 'z');
        }
    }

    println(n, m);
    println(s);
    println(t);
    return 0;
}
