#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = to_string(rnd.next(1, 9));
    } else if (mode == 1) {
        int len = rnd.next(2, 9);
        char digit = char('0' + rnd.next(1, 9));
        s.assign(len, digit);
    } else if (mode == 2) {
        int len = rnd.next(2, 9);
        s.push_back(char('0' + rnd.next(1, 9)));
        for (int i = 1; i < len; ++i) s.push_back(char('0' + rnd.next(0, 9)));
    } else if (mode == 3) {
        int len = rnd.next(2, 9);
        s.push_back(char('0' + rnd.next(1, 9)));
        for (int i = 1; i < len; ++i) {
            s.push_back(rnd.next(0, 2) == 0 ? '0' : char('0' + rnd.next(1, 9)));
        }
    } else if (mode == 4) {
        int len = rnd.next(2, 9);
        vector<char> digits;
        for (int i = 0; i < len; ++i) digits.push_back(char('0' + rnd.next(0, 9)));
        if (all_of(digits.begin(), digits.end(), [](char c) { return c == '0'; })) {
            digits[rnd.next(0, len - 1)] = char('1' + rnd.next(0, 8));
        }
        shuffle(digits.begin(), digits.end());
        if (digits[0] == '0') {
            for (int i = 1; i < len; ++i) {
                if (digits[i] != '0') {
                    swap(digits[0], digits[i]);
                    break;
                }
            }
        }
        s.assign(digits.begin(), digits.end());
    } else {
        s = "1000000000";
    }

    println(s);
    return 0;
}
