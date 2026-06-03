#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int numberFromDigits(const string& digits) {
    int value = 0;
    for (char digit : digits) value = value * 10 + (digit - '0');
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;

    if (mode == 0) {
        vector<int> boundaries = {0, 1, 9, 10, 99, 100, 9999999, 10000000};
        n = rnd.any(boundaries);
    } else if (mode == 1) {
        int len = rnd.next(1, 7);
        char digit = char('0' + rnd.next(0, 9));
        string digits(len, digit);
        n = numberFromDigits(digits);
    } else if (mode == 2) {
        int len = rnd.next(2, 7);
        string digits;
        digits += char('1' + rnd.next(0, 8));
        for (int i = 1; i < len; ++i) {
            digits += char('0' + rnd.next(0, 9));
        }
        n = numberFromDigits(digits);
    } else if (mode == 3) {
        int len = rnd.next(2, 7);
        string digits;
        char a = char('0' + rnd.next(0, 9));
        char b = char('0' + rnd.next(0, 9));
        if (a == b) b = char('0' + ((b - '0' + 1) % 10));
        digits += char('1' + rnd.next(0, 8));
        for (int i = 1; i < len; ++i) {
            digits += (rnd.next(0, 1) == 0 ? a : b);
        }
        n = numberFromDigits(digits);
    } else if (mode == 4) {
        n = 10000000 - rnd.next(0, 1000);
    } else {
        n = rnd.next(0, 10000000);
    }

    println(n);
    return 0;
}
