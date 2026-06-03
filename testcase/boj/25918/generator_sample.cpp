#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string alternating(int n, bool startsOpen) {
    string s;
    for (int i = 0; i < n; ++i) {
        bool open = (i % 2 == 0) == startsOpen;
        s += open ? '(' : ')';
    }
    return s;
}

string nestedBalanced(int pairs, bool startsOpen) {
    string s;
    s.append(pairs, startsOpen ? '(' : ')');
    s.append(pairs, startsOpen ? ')' : '(');
    return s;
}

string randomBalanced(int pairs) {
    string s;
    s.append(pairs, '(');
    s.append(pairs, ')');
    shuffle(s.begin(), s.end());
    return s;
}

string randomString(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += rnd.next(2) == 0 ? '(' : ')';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 5);
        s.assign(n, rnd.next(2) == 0 ? '(' : ')');
    } else if (mode == 1) {
        int n = rnd.next(1, 30);
        s = alternating(n, rnd.next(2) == 0);
    } else if (mode == 2) {
        int pairs = rnd.next(1, 15);
        s = nestedBalanced(pairs, true);
    } else if (mode == 3) {
        int pairs = rnd.next(1, 15);
        s = nestedBalanced(pairs, false);
    } else if (mode == 4) {
        int pairs = rnd.next(1, 15);
        s = randomBalanced(pairs);
    } else if (mode == 5) {
        int pairs = rnd.next(1, 12);
        s = randomBalanced(pairs);
        int inserts = rnd.next(1, 5);
        for (int i = 0; i < inserts; ++i) {
            int pos = rnd.next((int)s.size() + 1);
            s.insert(s.begin() + pos, rnd.next(2) == 0 ? '(' : ')');
        }
    } else {
        int n = rnd.next(1, 40);
        s = randomString(n);
    }

    println((int)s.size());
    println(s);
    return 0;
}
