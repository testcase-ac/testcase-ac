#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomFiller(int len) {
    const string alphabet = "BCDEFGHIJKMNOQRSTVWXYZ";
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

int smallGap(int parity) {
    int value = rnd.next(0, 5) * 2 + parity;
    if (rnd.next(0, 9) == 0) {
        value += rnd.next(10, 60) * 2;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string letters = "PAUL";
    vector<int> gaps(5);

    if (mode == 0) {
        for (int& gap : gaps) {
            gap = smallGap(0);
        }
    } else if (mode == 1) {
        for (int& gap : gaps) {
            gap = smallGap(0);
        }
        gaps[rnd.next(0, 4)] = smallGap(1);
    } else if (mode == 2) {
        for (int& gap : gaps) {
            gap = smallGap(rnd.next(0, 1));
        }
    } else if (mode == 3) {
        shuffle(letters.begin(), letters.end());
        if (letters == "PAUL") {
            swap(letters[0], letters[1]);
        }
        for (int& gap : gaps) {
            gap = smallGap(rnd.next(0, 1));
        }
    } else if (mode == 4) {
        for (int& gap : gaps) {
            gap = 0;
        }
        gaps[rnd.next(0, 4)] = rnd.next(0, 1);
    } else {
        for (int& gap : gaps) {
            gap = rnd.next(0, 20);
        }
    }

    string s;
    for (int i = 0; i < 4; ++i) {
        s += randomFiller(gaps[i]);
        s += letters[i];
    }
    s += randomFiller(gaps[4]);

    println(static_cast<int>(s.size()));
    println(s);

    return 0;
}
