#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string smallAlphabet = "ABC";
    const string fullAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(2, 30);
        s.assign(n, rnd.any(smallAlphabet));
    } else if (mode == 1) {
        int period = rnd.next(1, 6);
        string base = randomString(period, smallAlphabet);
        int repeats = rnd.next(2, 30 / period);
        s.reserve(period * repeats);
        for (int i = 0; i < repeats; ++i) {
            s += base;
        }
        int tail = rnd.next(0, period - 1);
        s += base.substr(0, tail);
    } else if (mode == 2) {
        int half = rnd.next(1, 14);
        string left = randomString(half, smallAlphabet);
        s = left;
        if (rnd.next(0, 1)) {
            s += rnd.any(smallAlphabet);
        }
        reverse(left.begin(), left.end());
        s += left;
    } else if (mode == 3) {
        s = randomString(rnd.next(2, 5), smallAlphabet);
        int steps = rnd.next(1, 4);
        for (int i = 0; i < steps && static_cast<int>(s.size()) < 30; ++i) {
            int keep = rnd.next(1, static_cast<int>(s.size()) - 1);
            string part;
            if (rnd.next(0, 1)) {
                part = s.substr(keep);
            } else {
                part = s.substr(0, keep);
            }
            if (rnd.next(0, 1)) {
                s = part + s;
            } else {
                s += part;
            }
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 30);
        s = randomString(n, fullAlphabet.substr(0, rnd.next(2, 8)));
    } else {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            char c = rnd.any(smallAlphabet);
            int len = rnd.next(1, 4);
            s.append(len, c);
        }
    }

    if (s.size() > 30) {
        s.resize(30);
    }
    if (s.size() < 2) {
        s += rnd.any(smallAlphabet);
    }

    println(s);
    return 0;
}
