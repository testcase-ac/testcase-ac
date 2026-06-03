#include "testlib.h"
#include <string>

using namespace std;

string randomLowercase(int length) {
    string s;
    for (int i = 0; i < length; ++i) {
        s += char('a' + rnd.next(26));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    string s;

    if (mode == 0) {
        s = randomLowercase(rnd.next(0, 20)) + "driip";
    } else if (mode == 1) {
        s = randomLowercase(rnd.next(1, 4));
    } else if (mode == 2) {
        string suffix = "driip";
        int pos = rnd.next(5);
        char c = suffix[pos];
        while (suffix[pos] == c) {
            c = char('a' + rnd.next(26));
        }
        suffix[pos] = c;
        s = randomLowercase(rnd.next(0, 20)) + suffix;
    } else if (mode == 3) {
        s = randomLowercase(rnd.next(0, 10)) + "driip" + randomLowercase(rnd.next(1, 10));
    } else if (mode == 4) {
        int length = rnd.next(25, 80);
        s = randomLowercase(length);
        if (rnd.next(2) == 0) {
            s.replace(length - 5, 5, "driip");
        }
    } else {
        int length = rnd.next(1, 30);
        s = string(length, rnd.next(2) == 0 ? 'a' : 'i');
    }

    println(s);
    return 0;
}
