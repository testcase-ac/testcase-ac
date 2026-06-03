#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char randomCharFrom(const string& alphabet) {
    return alphabet[rnd.next((int)alphabet.size())];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int length = rnd.next(1, 30);
    if (rnd.next(10) == 0) {
        length = rnd.next(31, 1000);
    }

    vector<string> alphabets = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "BCDEFGHIJKLMNOPQRSTUVWXYZ",
        "CDEFGHIJKLMNOPQRSTUVWXYZ",
        "DEFGHIJKLMNOPQRSTUVWXYZ",
    };

    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s += randomCharFrom(alphabets[mode]);
    }

    vector<string> targets = {
        "BCDF",
        "CDF",
        "DF",
        "DF",
    };
    for (int i = 0; i < length; ++i) {
        if (rnd.next(5) == 0) {
            s[i] = randomCharFrom(targets[mode]);
        }
    }

    if (mode < 3) {
        char required = char('A' + mode);
        s[rnd.next(length)] = required;
    }

    println(s);
    return 0;
}
