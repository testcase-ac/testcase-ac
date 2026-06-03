#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool validUnderCap(const string& s) {
    return s.size() < 9 || s <= "987654321";
}

string shuffledPrefix(int len) {
    vector<char> digits;
    for (char c = '1'; c <= '9'; ++c) digits.push_back(c);
    shuffle(digits.begin(), digits.end());

    string s;
    for (int i = 0; i < len; ++i) s.push_back(digits[i]);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string n;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n.push_back(char('1' + rnd.next(9)));
    } else if (mode == 1) {
        n = shuffledPrefix(rnd.next(2, 4));
    } else if (mode == 2) {
        n = shuffledPrefix(rnd.next(5, 8));
    } else if (mode == 3) {
        int len = rnd.next(2, 8);
        for (char c = '1'; c <= char('0' + len); ++c) n.push_back(c);
    } else if (mode == 4) {
        int len = rnd.next(2, 9);
        for (char c = '9'; (int)n.size() < len; --c) n.push_back(c);
        if (!validUnderCap(n)) n = "987654321";
    } else if (mode == 5) {
        do {
            n = shuffledPrefix(9);
        } while (!validUnderCap(n));
    } else {
        int len = rnd.next(1, 9);
        do {
            n = shuffledPrefix(len);
        } while (!validUnderCap(n));
    }

    println(n);
    return 0;
}
