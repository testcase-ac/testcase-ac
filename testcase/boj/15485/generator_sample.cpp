#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

string repeatChar(char ch, int count) {
    return string(count, ch);
}

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    string s;

    if (mode == 0) {
        vector<string> oneKind = {"a", "b", "c"};
        char ch = rnd.any(oneKind)[0];
        s = repeatChar(ch, rnd.next(1, 30));
    } else if (mode == 1) {
        int a = rnd.next(1, 12);
        int b = rnd.next(1, 12);
        int c = rnd.next(1, 12);
        s = repeatChar('a', a) + repeatChar('b', b) + repeatChar('c', c);
    } else if (mode == 2) {
        int a = rnd.next(1, 10);
        int b = rnd.next(1, 10);
        int c = rnd.next(1, 10);
        s = repeatChar('c', c) + repeatChar('b', b) + repeatChar('a', a);
    } else if (mode == 3) {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            s += repeatChar('a', rnd.next(1, 4));
            s += repeatChar('b', rnd.next(1, 4));
            s += repeatChar('c', rnd.next(1, 4));
        }
    } else if (mode == 4) {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            s += repeatChar('c', rnd.next(1, 4));
            s += repeatChar('a', rnd.next(1, 4));
            s += repeatChar('b', rnd.next(1, 4));
        }
    } else if (mode == 5) {
        int n = rnd.next(1, 80);
        s = randomString(n, "abc");
    } else if (mode == 6) {
        int n = rnd.next(1, 80);
        string alphabet = rnd.next(2) == 0 ? "ab" : "bc";
        s = randomString(n, alphabet);
    } else {
        int n = rnd.next(200, 500);
        s = randomString(n, "abc");
    }

    println(s);
    return 0;
}
