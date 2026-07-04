#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomNumber(int maxLen, const string& alphabet) {
    int len = rnd.next(1, maxLen);
    string s;
    s.reserve(len);
    s += rnd.any(string("123456789"));
    for (int i = 1; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

long long parseNumber(const string& s) {
    long long value = 0;
    for (char c : s) {
        value = value * 10 + (c - '0');
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 20);
    vector<long long> values;
    values.reserve(n);

    if (mode == 0) {
        n = rnd.next(2, 8);
        vector<long long> pool = {1, 6, 9, 16, 19, 60, 66, 69, 90, 96, 99, 1000000000000000000LL};
        for (int i = 0; i < n; ++i) {
            values.push_back(rnd.any(pool));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 15);
        for (int i = 0; i < n; ++i) {
            values.push_back(parseNumber(randomNumber(12, "06669999")));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            string alphabet = rnd.next(0, 1) ? "0123456789" : "016789";
            values.push_back(parseNumber(randomNumber(18, alphabet)));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        long long cur = rnd.next(1LL, 200LL);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0LL, 80LL);
            string s = toString(cur);
            for (char& c : s) {
                if ((c == '6' || c == '9') && rnd.next(0, 1)) {
                    c = (c == '6' ? '9' : '6');
                }
            }
            values.push_back(parseNumber(s));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 18);
        long long cur = rnd.next(300LL, 2000LL);
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0LL, 90LL);
            values.push_back(max(1LL, cur));
        }
    } else {
        n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            long long offset = rnd.next(0LL, 999999999LL);
            values.push_back(1000000000000000000LL - offset);
        }
        if (rnd.next(0, 1)) {
            shuffle(values.begin(), values.end());
        }
    }

    println(n);
    for (long long value : values) {
        println(value);
    }

    return 0;
}
