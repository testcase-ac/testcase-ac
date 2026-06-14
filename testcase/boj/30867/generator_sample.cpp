#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static char noiseChar() {
    static const string letters = "abcdefgijklmopqrstuvxyz";
    return rnd.any(letters);
}

static string alternatingWh(int len) {
    string s;
    s.reserve(len);
    char first = rnd.next(0, 1) ? 'w' : 'h';
    for (int i = 0; i < len; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == 'w' ? 'h' : 'w'));
    }
    return s;
}

static string blockyWh(int len) {
    string s;
    while ((int)s.size() < len) {
        char c = rnd.next(0, 1) ? 'w' : 'h';
        int take = rnd.next(1, min(6, len - (int)s.size()));
        s.append(take, c);
        if ((int)s.size() < len && rnd.next(0, 3) == 0) {
            s.push_back(noiseChar());
        }
    }
    s.resize(len);
    return s;
}

static string noisyWh(int len) {
    string s(len, 'a');
    int whBias = rnd.next(20, 85);
    for (char& c : s) {
        int roll = rnd.next(1, 100);
        if (roll <= whBias) {
            c = rnd.next(0, 1) ? 'w' : 'h';
        } else {
            c = noiseChar();
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int l;
    if (mode == 0) {
        l = rnd.next(1, 6);
    } else {
        l = rnd.next(2, 35);
    }

    int n;
    if (rnd.next(0, 4) == 0) {
        n = rnd.next(100000, 200000);
    } else {
        n = rnd.next(1, min(60, 3 * max(1, l)));
    }

    string s;
    if (mode == 0) {
        s.assign(l, noiseChar());
    } else if (mode == 1) {
        s = alternatingWh(l);
    } else if (mode == 2) {
        s = blockyWh(l);
    } else if (mode == 3) {
        int left = rnd.next(1, l);
        s.assign(left, 'w');
        s.append(l - left, 'h');
    } else if (mode == 4) {
        int left = rnd.next(0, l);
        s.assign(left, 'h');
        s.append(l - left, 'w');
    } else {
        s = noisyWh(l);
    }

    println(l, n);
    println(s);
    return 0;
}
