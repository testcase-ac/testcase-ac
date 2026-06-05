#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int fromDigits(string s) {
    return stoi(s);
}

string shuffledDigits(int len, bool allowZero) {
    string s;
    s += char('1' + rnd.next(9));
    for (int i = 1; i < len; ++i) {
        int lo = allowZero ? 0 : 1;
        s += char('0' + rnd.next(lo, 9));
    }
    shuffle(s.begin(), s.end());
    if (s[0] == '0') {
        int pos = rnd.next(1, len - 1);
        swap(s[0], s[pos]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 0;

    if (mode == 0) {
        n = rnd.next(0, 999999);
    } else if (mode == 1) {
        int len = rnd.next(1, 6);
        n = fromDigits(shuffledDigits(len, true));
    } else if (mode == 2) {
        int len = rnd.next(1, 6);
        char digit = char('1' + rnd.next(9));
        n = fromDigits(string(len, digit));
    } else if (mode == 3) {
        int len = rnd.next(2, 6);
        string s(len, '0');
        s[0] = char('1' + rnd.next(9));
        int extraNonZero = rnd.next(0, len - 1);
        for (int i = 0; i < extraNonZero; ++i) {
            int pos = rnd.next(1, len - 1);
            s[pos] = char('1' + rnd.next(9));
        }
        n = fromDigits(s);
    } else if (mode == 4) {
        int len = rnd.next(1, 6);
        string s = shuffledDigits(len, true);
        sort(s.begin(), s.end());
        if (s[0] == '0') {
            int pos = 1;
            while (pos < len && s[pos] == '0') ++pos;
            swap(s[0], s[pos]);
        }
        if (rnd.next(2)) reverse(s.begin(), s.end());
        n = fromDigits(s);
    } else {
        n = rnd.any(vector<int>{0, 1, 9, 10, 99, 100, 101, 909090, 999999});
    }

    println(n);
    return 0;
}
