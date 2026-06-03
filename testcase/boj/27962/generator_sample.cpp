#include "testlib.h"
#include <string>

using namespace std;

char randomChar(int alphabetSize) {
    return char('a' + rnd.next(alphabetSize));
}

string randomString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomChar(alphabetSize));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(2, 40);
    int alphabetSize = rnd.next(1, 8);
    string s;

    if (mode == 0) {
        s.assign(n, randomChar(alphabetSize));
    } else if (mode == 1) {
        s = randomString(n, alphabetSize);
    } else if (mode == 2) {
        int period = rnd.next(1, min(n, 8));
        string base = randomString(period, alphabetSize);
        for (int i = 0; i < n; ++i) {
            s.push_back(base[i % period]);
        }
    } else if (mode == 3) {
        int len = rnd.next(1, n);
        int suffixStart = n - len;
        s = randomString(n, alphabetSize);
        string t = randomString(len, max(2, alphabetSize));
        int diffAt = rnd.next(len);
        for (int i = 0; i < len; ++i) {
            s[i] = t[i];
            s[suffixStart + i] = t[i];
        }
        char changed = s[suffixStart + diffAt];
        do {
            s[suffixStart + diffAt] = randomChar(max(2, alphabetSize));
        } while (s[suffixStart + diffAt] == changed);
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        s = randomString(n, 2);
    } else {
        int len = rnd.next(1, n);
        int suffixStart = n - len;
        s = randomString(n, alphabetSize);
        string t = randomString(len, alphabetSize);
        for (int i = 0; i < len; ++i) {
            s[i] = t[i];
            s[suffixStart + i] = t[i];
        }
    }

    println((int)s.size());
    println(s);

    return 0;
}
