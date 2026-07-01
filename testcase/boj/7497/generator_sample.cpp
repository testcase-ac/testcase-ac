#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values = {
        1,
        9,
        10,
        11,
        99,
        100,
        101,
        999,
        1000,
        1001,
        1999,
        9999,
        10000,
        99999,
        101090000,
        1999999999,
        2000000000,
    };

    int mode = rnd.next(0, 5);
    int extraCount = rnd.next(1, 12);
    for (int i = 0; i < extraCount; ++i) {
        if (mode == 0) {
            values.push_back(rnd.next(1, 200));
        } else if (mode == 1) {
            int power = 1;
            int digits = rnd.next(1, 9);
            for (int j = 0; j < digits; ++j) power *= 10;
            int delta = rnd.next(-20, 20);
            values.push_back(max(1, min(2000000000, power + delta)));
        } else if (mode == 2) {
            string s;
            int len = rnd.next(1, 10);
            s += char('1' + rnd.next(0, 8));
            for (int j = 1; j < len; ++j) {
                s += rnd.any(string("000123456789"));
            }
            long long x = stoll(s);
            values.push_back((int)min<long long>(x, 2000000000LL));
        } else if (mode == 3) {
            string s;
            int len = rnd.next(1, 10);
            for (int j = 0; j < len; ++j) {
                s += char('1' + rnd.next(0, 8));
            }
            long long x = stoll(s);
            values.push_back((int)min<long long>(x, 2000000000LL));
        } else if (mode == 4) {
            values.push_back(rnd.next(1900000000, 2000000000));
        } else {
            values.push_back(rnd.next(1, 2000000000));
        }
    }

    shuffle(values.begin(), values.end());
    values.resize(rnd.next(1, min<int>(25, values.size())));

    for (int value : values) {
        println(value);
    }

    return 0;
}
