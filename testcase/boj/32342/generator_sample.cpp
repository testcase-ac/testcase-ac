#include "testlib.h"

#include <string>

using namespace std;

string randomString(int n, int wPercent) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.next(1, 100) <= wPercent ? 'W' : 'O';
    }
    return s;
}

string alternatingString(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += (i % 2 == 0) ? first : (first == 'W' ? 'O' : 'W');
    }
    return s;
}

string blockString(int n) {
    string s;
    char cur = rnd.next(0, 1) ? 'W' : 'O';
    while ((int)s.size() < n) {
        int remaining = n - (int)s.size();
        int run = rnd.next(1, min(remaining, rnd.next(1, 8)));
        s.append(run, cur);
        cur = (cur == 'W') ? 'O' : 'W';
    }
    return s;
}

string wowRichString(int n) {
    string s;
    while ((int)s.size() < n) {
        int choice = rnd.next(0, 4);
        if (choice <= 1) {
            s += "WOW";
        } else if (choice == 2) {
            s += "OW";
        } else if (choice == 3) {
            s += "WW";
        } else {
            s += rnd.next(0, 1) ? 'W' : 'O';
        }
    }
    s.resize(n);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(1, 25);
    println(q);
    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 5);
        int n;
        if (mode == 0) {
            n = rnd.next(1, 6);
        } else if (mode == 5) {
            n = rnd.next(60, 180);
        } else {
            n = rnd.next(7, 60);
        }

        string s;
        if (mode == 0) {
            s = randomString(n, rnd.next(0, 100));
        } else if (mode == 1) {
            s = alternatingString(n, 'W');
        } else if (mode == 2) {
            s = alternatingString(n, 'O');
        } else if (mode == 3) {
            s = blockString(n);
        } else if (mode == 4) {
            s = wowRichString(n);
        } else {
            s = randomString(n, rnd.next(20, 80));
        }

        println(s);
    }

    return 0;
}
