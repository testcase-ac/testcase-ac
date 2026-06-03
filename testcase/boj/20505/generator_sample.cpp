#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int len = rnd.next(1, 35);
    string n;

    if (mode == 0) {
        n += char('1' + rnd.next(0, 8));
    } else if (mode == 1) {
        n += char('1' + rnd.next(0, 8));
        len = rnd.next(2, 45);
        for (int i = 1; i < len; ++i) n += '0';
    } else if (mode == 2) {
        char digit = char('1' + rnd.next(0, 8));
        len = rnd.next(2, 40);
        n.assign(len, digit);
    } else if (mode == 3) {
        len = rnd.next(3, 45);
        char a = char('1' + rnd.next(0, 8));
        char b = char('0' + rnd.next(0, 9));
        for (int i = 0; i < len; ++i) n += (i % 2 == 0 ? a : b);
    } else if (mode == 4) {
        len = rnd.next(4, 50);
        n += char('1' + rnd.next(0, 8));
        for (int i = 1; i < len; ++i) {
            n += (rnd.next(0, 99) < 70 ? '0' : char('1' + rnd.next(0, 8)));
        }
    } else if (mode == 5) {
        len = rnd.next(8, 80);
        n += char('1' + rnd.next(0, 8));
        for (int i = 1; i < len; ++i) n += char('0' + rnd.next(0, 9));
    } else {
        len = rnd.next(2, 60);
        string block;
        int blockLen = rnd.next(1, 5);
        for (int i = 0; i < blockLen; ++i) block += char('0' + rnd.next(0, 9));
        if (block[0] == '0') block[0] = char('1' + rnd.next(0, 8));
        while ((int)n.size() < len) n += block;
        n.resize(len);
    }

    println(n);
    return 0;
}
