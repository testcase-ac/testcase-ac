#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

string randomSafeLetters(int len) {
    const string alphabet = "abcdefhjklmopqrsuvwxyz";
    string s;
    for (int i = 0; i < len; i++) {
        s += rnd.any(alphabet);
    }
    return s;
}

string repeatLong(int count) {
    string s;
    for (int i = 0; i < count; i++) {
        s += "long";
    }
    return s;
}

void appendWithinLimit(string& s, const string& part) {
    if ((int)s.size() + (int)part.size() <= 80) {
        s += part;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    string s;

    if (mode == 0) {
        s = randomSafeLetters(rnd.next(1, 30));
    } else if (mode == 1) {
        int before = rnd.next(0, 12);
        int after = rnd.next(0, 12);
        s = randomSafeLetters(before) + "long" + randomSafeLetters(after);
    } else if (mode == 2) {
        int count = rnd.next(1, 10);
        s = repeatLong(count);
    } else if (mode == 3) {
        int groups = rnd.next(2, 6);
        for (int i = 0; i < groups; i++) {
            appendWithinLimit(s, repeatLong(rnd.next(1, 4)));
            if (i + 1 < groups) {
                appendWithinLimit(s, randomSafeLetters(rnd.next(1, 6)));
            }
        }
        appendWithinLimit(s, randomSafeLetters(rnd.next(0, 8)));
    } else {
        int target = rnd.next(55, 80);
        while ((int)s.size() < target) {
            if (rnd.next(0, 2) == 0 && (int)s.size() + 4 <= target) {
                s += "long";
            } else {
                s += rnd.any(string("abcdefhjklmopqrsuvwxyz"));
            }
        }
    }

    println((int)s.size());
    println(s);

    return 0;
}
