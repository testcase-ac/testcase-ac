#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomDigits(int len, bool nonzeroFirst) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        int lo = (i == 0 && nonzeroFirst) ? 1 : 0;
        s.push_back(char('0' + rnd.next(lo, 9)));
    }
    return s;
}

string powerOfTenLike(int len) {
    string s = "1" + string(len - 1, '0');
    if (len > 1 && rnd.next(0, 1)) {
        int pos = rnd.next(1, len - 1);
        s[pos] = char('1' + rnd.next(0, 8));
    }
    return s;
}

string carryHeavyPositive(int len) {
    string s = randomDigits(len, true);
    int suffix = rnd.next(1, min(len, 8));
    for (int i = len - suffix; i < len; ++i) {
        s[i] = rnd.any(string("089"));
    }
    if (s.size() > 1 && s[0] == '0') s[0] = char('1' + rnd.next(0, 8));
    if (rnd.next(0, 1)) {
        int pos = rnd.next(0, len - 1);
        s[pos] = rnd.any(string("123"));
    }
    return s;
}

string negativeNumber(int len) {
    string s = randomDigits(len, true);
    if (rnd.next(0, 2) == 0) {
        int suffix = rnd.next(1, min(len, 8));
        for (int i = len - suffix; i < len; ++i) s[i] = '9';
    }
    return "-" + s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(8, 20);
    vector<string> values;
    values.reserve(cases);

    vector<string> seeds = {"0", "1", "9", "10", "-1", "-9", "99", "1000"};
    shuffle(seeds.begin(), seeds.end());
    int fixedCount = rnd.next(2, min(5, cases));
    for (int i = 0; i < fixedCount; ++i) values.push_back(seeds[i]);

    while (static_cast<int>(values.size()) < cases) {
        int mode = rnd.next(0, 5);
        int len = rnd.next(1, 4);

        if (mode == 0) {
            values.push_back(to_string(rnd.next(-250, 250)));
        } else if (mode == 1) {
            values.push_back(powerOfTenLike(len));
        } else if (mode == 2) {
            values.push_back(carryHeavyPositive(len));
        } else if (mode == 3) {
            values.push_back(negativeNumber(len));
        } else if (mode == 4) {
            values.push_back(string(len, '9'));
        } else if (mode == 5) {
            string s = randomDigits(len, true);
            int zeros = rnd.next(1, min(len, 10));
            for (int i = len - zeros; i < len; ++i) s[i] = '0';
            if (s.size() > 1 && s[0] == '0') s[0] = char('1' + rnd.next(0, 8));
            values.push_back(s);
        }
    }

    for (const string& value : values) println(value);
    println("END");
    return 0;
}
