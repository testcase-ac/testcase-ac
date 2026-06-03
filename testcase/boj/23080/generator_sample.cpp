#include "testlib.h"

#include <algorithm>
#include <string>
using namespace std;

string randomLowercaseString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('a' + rnd.next(alphabetSize)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(3, 10);
    int mode = rnd.next(6);
    int len = 1;

    if (mode == 0) {
        len = rnd.next(1, min(12, k * 3));
    } else if (mode == 1) {
        int blocks = rnd.next(1, 8);
        len = blocks * k;
    } else if (mode == 2) {
        int blocks = rnd.next(1, 8);
        len = blocks * k + rnd.next(1, k - 1);
    } else if (mode == 3) {
        len = rnd.next(20, 80);
    } else if (mode == 4) {
        len = rnd.next(950, 1000);
    } else {
        len = rnd.next(1, 1000);
    }

    int alphabetSize = rnd.next(1, 26);
    string s = randomLowercaseString(len, alphabetSize);

    if (mode == 3) {
        string pattern = randomLowercaseString(rnd.next(1, min(10, len)), alphabetSize);
        for (int i = 0; i < len; ++i) {
            s[i] = pattern[i % int(pattern.size())];
        }
    } else if (mode == 4 && rnd.next(2) == 0) {
        sort(s.begin(), s.end());
    }

    println(k);
    println(s);

    return 0;
}
