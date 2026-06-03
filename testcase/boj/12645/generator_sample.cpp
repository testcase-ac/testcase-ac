#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int makePatternNumber() {
    int len = rnd.next(1, 7);
    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        char d = char('1' + rnd.next(0, 8));
        s.assign(len, d);
    } else if (mode == 1) {
        s += char('1' + rnd.next(0, 8));
        for (int i = 1; i < len; ++i) s += char('0' + rnd.next(0, 2));
    } else if (mode == 2) {
        int start = rnd.next(1, 9);
        for (int i = 0; i < len; ++i) s += char('0' + max(0, start - i));
    } else if (mode == 3) {
        int high = rnd.next(1, 9);
        for (int i = 0; i < len; ++i) s += char('0' + rnd.next(0, high));
        if (s[0] == '0') s[0] = char('1' + rnd.next(0, 8));
    } else {
        int base = rnd.next(1, 999);
        int zeros = rnd.next(1, 3);
        s = to_string(base);
        s.append(zeros, '0');
    }

    int value = stoi(s);
    if (value < 1) return 1;
    if (value > 1000000) return rnd.next(1, 1000000);
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> cases;
    int t = rnd.next(1, 50);
    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 9);
        int n;
        if (mode <= 4) {
            n = makePatternNumber();
        } else if (mode <= 6) {
            n = rnd.next(1, 1000);
        } else if (mode == 7) {
            n = rnd.next(999000, 1000000);
        } else {
            n = rnd.next(1, 1000000);
        }
        cases.push_back(n);
    }

    if (t >= 3 && rnd.next(0, 1)) {
        cases[0] = 1;
        cases[1] = 987654;
        cases[2] = 1000000;
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (int n : cases) println(n);

    return 0;
}
