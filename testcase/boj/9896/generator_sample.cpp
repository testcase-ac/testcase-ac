#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    string bits(n, '0');

    if (mode == 0) {
        char bit = char('0' + rnd.next(0, 1));
        fill(bits.begin(), bits.end(), bit);
    } else if (mode == 1) {
        char first = char('0' + rnd.next(0, 1));
        for (int i = 0; i < n; ++i) {
            bits[i] = char('0' + ((i & 1) ^ (first - '0')));
        }
    } else if (mode == 2) {
        int changes = rnd.next(1, min(n, 6));
        char bit = char('0' + rnd.next(0, 1));
        int pos = 0;
        for (int block = 0; block < changes && pos < n; ++block) {
            int remainingBlocks = changes - block;
            int len = rnd.next(1, n - pos - remainingBlocks + 1);
            fill(bits.begin() + pos, bits.begin() + pos + len, bit);
            pos += len;
            bit = char('1' - bit + '0');
        }
        fill(bits.begin() + pos, bits.end(), bit);
    } else if (mode == 3) {
        fill(bits.begin(), bits.end(), '0');
        int ones = rnd.next(1, n);
        for (int i = 0; i < ones; ++i) {
            bits[rnd.next(0, n - 1)] = '1';
        }
    } else if (mode == 4) {
        fill(bits.begin(), bits.end(), '1');
        int zeros = rnd.next(1, n);
        for (int i = 0; i < zeros; ++i) {
            bits[rnd.next(0, n - 1)] = '0';
        }
    } else {
        for (int i = 0; i < n; ++i) {
            bits[i] = char('0' + rnd.next(0, 1));
        }
    }

    println(n);
    println(bits);

    return 0;
}
