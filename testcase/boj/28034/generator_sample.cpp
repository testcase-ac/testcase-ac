#include "testlib.h"

#include <string>

using namespace std;

char randomCow() {
    return rnd.next(0, 1) == 0 ? 'B' : 'E';
}

char opposite(char c) {
    return c == 'B' ? 'E' : 'B';
}

string randomCowString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomCow());
    }
    return s;
}

string alternatingString(int n) {
    string s;
    s.reserve(n);
    char c = randomCow();
    for (int i = 0; i < n; ++i) {
        s.push_back(i % 2 == 0 ? c : opposite(c));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 30);
    string s;

    if (mode == 0) {
        s = string(n, 'F');
    } else if (mode == 1) {
        s = randomCowString(n);
    } else if (mode == 2) {
        s = alternatingString(n);
    } else if (mode == 3) {
        s = randomCowString(n);
        int len = rnd.next(1, n);
        int start = rnd.next(0, n - len);
        for (int i = 0; i < len; ++i) {
            s[start + i] = 'F';
        }
    } else if (mode == 4) {
        s = randomCowString(n);
        int prefix = rnd.next(1, n);
        for (int i = 0; i < prefix; ++i) {
            s[i] = 'F';
        }
        if (prefix < n && rnd.next(0, 1)) {
            int suffix = rnd.next(1, n - prefix);
            for (int i = 0; i < suffix; ++i) {
                s[n - 1 - i] = 'F';
            }
        }
    } else if (mode == 5) {
        s = randomCowString(n);
        int i = 0;
        while (i < n) {
            int len = rnd.next(1, min(5, n - i));
            char c = rnd.any(string("BEF"));
            for (int j = 0; j < len; ++j) {
                s[i + j] = c;
            }
            i += len;
        }
    } else if (mode == 6) {
        s = alternatingString(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 35) {
                s[i] = 'F';
            }
        }
    } else {
        n = rnd.next(25, 80);
        s = randomCowString(n);
        int runs = rnd.next(3, 10);
        for (int r = 0; r < runs; ++r) {
            int len = rnd.next(1, min(12, n));
            int start = rnd.next(0, n - len);
            for (int i = 0; i < len; ++i) {
                s[start + i] = 'F';
            }
        }
    }

    println(n);
    println(s);
    return 0;
}
