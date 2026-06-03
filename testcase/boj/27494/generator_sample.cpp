#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int bounded(long long value) {
    return (int)max(1LL, min(10000000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> digitBoundaries = {
        9, 10, 99, 100, 999, 1000, 1999, 2000, 2022, 2023, 2024,
        9999, 10000, 99999, 100000, 999999, 1000000, 9999999, 10000000,
    };

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.next(1, 2500);
    } else if (mode == 1) {
        int center = rnd.any(digitBoundaries);
        n = bounded((long long)center + rnd.next(-30, 30));
    } else if (mode == 2) {
        string prefix = rnd.next(0, 1) ? to_string(rnd.next(1, 99)) : "";
        string suffix = rnd.next(0, 1) ? to_string(rnd.next(0, 999)) : "";
        n = bounded(stoll(prefix + "2023" + suffix));
    } else if (mode == 3) {
        int high = rnd.next(1000000, 10000000);
        int low = max(1, high - rnd.next(0, 5000));
        n = rnd.next(low, high);
    } else if (mode == 4) {
        n = rnd.next(1, 10000000);
    } else {
        int length = rnd.next(4, 8);
        string s;
        for (int i = 0; i < length; ++i) {
            s += char('0' + rnd.next(0, 9));
        }
        s[0] = char('1' + rnd.next(0, 8));
        n = bounded(stoll(s));
    }

    println(n);
    return 0;
}
