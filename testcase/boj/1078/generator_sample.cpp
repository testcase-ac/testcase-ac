#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

long long reverseNumber(long long x) {
    long long result = 0;
    while (x > 0) {
        result = result * 10 + x % 10;
        x /= 10;
    }
    return result;
}

long long randomXWithLength(int len) {
    string s;
    s += char('1' + rnd.next(9));
    for (int i = 1; i < len; ++i) {
        if (rnd.next(100) < 35) {
            s += '0';
        } else {
            s += char('0' + rnd.next(10));
        }
    }
    return stoll(s);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int d = 1;

    if (mode == 0) {
        d = rnd.next(1, 120);
    } else if (mode == 1) {
        d = rnd.next(999880, 1000000);
    } else if (mode == 2) {
        d = rnd.next(1, 111111);
        d *= 9;
        if (d > 1000000) d = 1000000;
    } else if (mode == 3) {
        d = rnd.next(1, 1000000);
        if (d % 9 == 0) {
            d += rnd.next(1, 8);
            if (d > 1000000) d -= 8;
        }
    } else if (mode == 4) {
        vector<int> interesting = {
            9, 18, 45, 90, 99, 108, 900, 909, 990, 999,
            1989, 4275, 900000, 990000, 999999, 1000000
        };
        d = rnd.any(interesting);
    } else {
        for (int attempt = 0; attempt < 200; ++attempt) {
            int len = rnd.next(2, 10);
            long long x = randomXWithLength(len);
            long long diff = x - reverseNumber(x);
            if (1 <= diff && diff <= 1000000) {
                d = int(diff);
                break;
            }
        }
    }

    println(d);
    return 0;
}
