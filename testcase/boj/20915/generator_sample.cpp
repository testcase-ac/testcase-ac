#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static string randomDigits(int length, const string& alphabet) {
    string s;
    for (int i = 0; i < length; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

static string makeCase(int mode) {
    int length;
    string s;

    if (mode == 0) {
        length = rnd.next(2, 8);
        s = randomDigits(length, "0");
        s[rnd.next(length)] = rnd.any(string("123456789"));
    } else if (mode == 1) {
        length = rnd.next(2, 18);
        s = randomDigits(length, "69");
    } else if (mode == 2) {
        length = rnd.next(2, 18);
        char digit = rnd.any(string("012345789"));
        s = string(length, digit);
    } else if (mode == 3) {
        length = rnd.next(2, 12);
        s = randomDigits(length, "0123456789");
        sort(s.begin(), s.end());
        if (rnd.next(2) == 1) {
            reverse(s.begin(), s.end());
        }
    } else if (mode == 4) {
        length = rnd.next(10, 18);
        s = randomDigits(length, "789");
    } else {
        length = rnd.next(2, 18);
        string alphabet = rnd.any(vector<string>{"01", "012", "13579", "02468", "0123456789"});
        s = randomDigits(length, alphabet);
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);
    for (int i = 0; i < t; ++i) {
        println(makeCase(rnd.next(6)));
    }

    return 0;
}
