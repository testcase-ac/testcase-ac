#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int digitCount;
    if (mode == 0) {
        digitCount = 1;
    } else if (mode == 1) {
        digitCount = 2;
    } else if (mode == 2) {
        digitCount = rnd.next(3, 8);
    } else if (mode == 3) {
        digitCount = rnd.next(9, 20);
    } else {
        digitCount = rnd.next(21, 49);
    }

    string name = "T";
    for (int i = 0; i + 1 < digitCount; ++i) {
        if (mode == 4) {
            name += char('1' + (i % 3));
        } else {
            name += char('1' + rnd.next(0, 2));
        }
    }

    int lastDigit;
    if (mode == 0) {
        lastDigit = rnd.next(1, 4);
    } else if (mode == 3) {
        lastDigit = 4;
    } else {
        lastDigit = rnd.next(1, 4);
    }
    name += char('0' + lastDigit);

    println(name);
    return 0;
}
