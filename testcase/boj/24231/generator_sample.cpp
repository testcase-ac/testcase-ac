#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string randomBits(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('0' + rnd.next(2)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = rnd.next(2, 40);
    if (rnd.next(5) == 0) n = rnd.next(250, 300);

    string s;
    if (mode == 0) {
        n = rnd.next(2, 8);
        s = randomBits(n);
    } else if (mode == 1) {
        s.assign(n, char('0' + rnd.next(2)));
    } else if (mode == 2) {
        int first = rnd.next(2);
        for (int i = 0; i < n; ++i) {
            s.push_back(char('0' + ((first + i) & 1)));
        }
    } else if (mode == 3) {
        while ((int)s.size() < n) {
            int len = rnd.next(1, 8);
            char bit = char('0' + rnd.next(2));
            s.append(min(len, n - (int)s.size()), bit);
        }
    } else if (mode == 4) {
        n = rnd.next(1, 20) * 2;
        string left = randomBits(n / 2);
        s = left;
        reverse(left.begin(), left.end());
        for (char c : left) {
            s.push_back(c == '0' ? '1' : '0');
        }
    } else if (mode == 5) {
        n = rnd.next(1, 20) * 2 + 1;
        s = randomBits(n);
    } else {
        s = randomBits(n);
    }

    println(s);
    return 0;
}
