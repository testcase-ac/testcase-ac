#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long makeRumi(int prefix, int middle) {
    string s = to_string(prefix);
    if (middle < 0) {
        return stoll(s + s);
    }
    return stoll(s + char('0' + middle) + s);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values = {
        1,
        2,
        9,
        10,
        11,
        99,
        100,
        101,
        999,
        1000,
        999999998,
        999999999,
        1000000000,
    };

    int mode = rnd.next(0, 4);
    int t = rnd.next(1, 10);

    while ((int)values.size() < t + 8) {
        int n;
        if (mode == 0) {
            n = rnd.next(1, 250);
        } else if (mode == 1) {
            int digits = rnd.next(1, 10);
            int base = 1;
            for (int i = 1; i < digits; ++i) base *= 10;
            n = rnd.next(max(1, base - 5), min(1000000000, base + 5));
        } else if (mode == 2) {
            int prefixLimit = rnd.next(10, 10000);
            int aPrefix = rnd.next(1, prefixLimit);
            int bPrefix = rnd.next(1, prefixLimit);
            long long a = makeRumi(aPrefix, rnd.next(-1, 9));
            long long b = makeRumi(bPrefix, rnd.next(-1, 9));
            n = (int)min(1000000000LL, a + b);
        } else if (mode == 3) {
            n = rnd.next(999900000, 1000000000);
        } else {
            n = rnd.next(1, 1000000000);
        }
        values.push_back(n);
    }

    shuffle(values.begin(), values.end());
    values.resize(t);

    println(t);
    for (int n : values) {
        println(n);
    }

    return 0;
}
