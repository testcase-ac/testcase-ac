#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<char> letters;
    for (char c = 'A'; c <= 'Z'; ++c) {
        letters.push_back(c);
    }

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        shuffle(letters.begin(), letters.end());
        for (char c : letters) {
            s += c;
            s += c;
        }
    } else if (mode == 1) {
        shuffle(letters.begin(), letters.end());
        for (char c : letters) {
            s += c;
        }
        for (char c : letters) {
            s += c;
        }
    } else if (mode == 2) {
        shuffle(letters.begin(), letters.end());
        for (char c : letters) {
            s += c;
        }
        reverse(letters.begin(), letters.end());
        for (char c : letters) {
            s += c;
        }
    } else if (mode == 3) {
        shuffle(letters.begin(), letters.end());
        int active = rnd.next(2, 12);
        vector<char> group(letters.begin(), letters.begin() + active);
        vector<char> rest(letters.begin() + active, letters.end());

        for (char c : group) {
            s += c;
        }
        shuffle(group.begin(), group.end());
        for (char c : group) {
            s += c;
        }
        shuffle(rest.begin(), rest.end());
        for (char c : rest) {
            s += c;
            s += c;
        }
    } else if (mode == 4) {
        vector<char> open;
        vector<char> close;
        shuffle(letters.begin(), letters.end());
        for (char c : letters) {
            if (rnd.next(0, 1) == 0) {
                s += c;
                open.push_back(c);
            } else {
                close.push_back(c);
            }
        }
        shuffle(open.begin(), open.end());
        for (char c : open) {
            s += c;
        }
        shuffle(close.begin(), close.end());
        for (char c : close) {
            s += c;
            s += c;
        }
    } else {
        vector<char> slots;
        for (char c : letters) {
            slots.push_back(c);
            slots.push_back(c);
        }
        shuffle(slots.begin(), slots.end());
        s.assign(slots.begin(), slots.end());
    }

    println(s);
    return 0;
}
