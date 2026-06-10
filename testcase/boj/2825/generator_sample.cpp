#include "testlib.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

long long makeNumberWithDigit(int requiredDigit, int maxLen) {
    int len = rnd.next(1, maxLen);
    string s;
    s.reserve(len);

    if (len == 1) {
        if (requiredDigit == 0) return rnd.next(1, 9);
        return requiredDigit;
    }

    int pos = rnd.next(len);
    for (int i = 0; i < len; ++i) {
        int d;
        if (i == pos) {
            d = requiredDigit;
        } else if (i == 0) {
            d = rnd.next(1, 9);
        } else {
            d = rnd.next(0, 9);
        }
        if (i == 0 && d == 0) d = rnd.next(1, 9);
        s.push_back(char('0' + d));
    }

    return stoll(s);
}

long long makeNumberFromDigits(const vector<int>& digits, int maxLen) {
    int len = rnd.next(1, maxLen);
    string s;
    s.reserve(len);

    vector<int> nonZero;
    for (int d : digits) {
        if (d != 0) nonZero.push_back(d);
    }
    if (nonZero.empty()) nonZero.push_back(1);

    s.push_back(char('0' + rnd.any(nonZero)));
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.any(digits)));
    }

    return stoll(s);
}

void addUnique(set<long long>& values, long long value) {
    if (1 <= value && value <= 1000000000000000000LL) {
        values.insert(value);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 35);
    set<long long> values;

    if (mode == 0) {
        // Mostly disjoint digit families with a few accidental overlaps.
        vector<vector<int>> groups = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0}};
        shuffle(groups.begin(), groups.end());
        for (int i = 0; i < n; ++i) {
            const vector<int>& group = groups[i % groups.size()];
            addUnique(values, makeNumberFromDigits(group, rnd.next(1, 8)));
        }
    } else if (mode == 1) {
        // Many numbers share one required digit, creating many friend pairs.
        int commonDigit = rnd.next(0, 9);
        for (int i = 0; i < n; ++i) {
            addUnique(values, makeNumberWithDigit(commonDigit, rnd.next(1, 18)));
        }
    } else if (mode == 2) {
        // Boundary and repeated-digit shapes.
        vector<long long> special = {
            1LL, 9LL, 10LL, 11LL, 99LL, 100LL, 101LL, 1000LL,
            999999999999999999LL, 1000000000000000000LL
        };
        shuffle(special.begin(), special.end());
        for (long long value : special) addUnique(values, value);
        while ((int)values.size() < n) {
            int d = rnd.next(1, 9);
            int len = rnd.next(1, 18);
            string s(len, char('0' + d));
            addUnique(values, stoll(s));
        }
    } else if (mode == 3) {
        // Small readable numbers with arbitrary digit masks.
        while ((int)values.size() < n) {
            addUnique(values, rnd.next(1, 99999));
        }
    } else {
        // Mixed sizes, including occasional long values.
        while ((int)values.size() < n) {
            int len = rnd.next(1, 18);
            string s;
            s.reserve(len);
            s.push_back(char('0' + rnd.next(1, 9)));
            for (int i = 1; i < len; ++i) {
                s.push_back(char('0' + rnd.next(0, 9)));
            }
            addUnique(values, stoll(s));
        }
    }

    while ((int)values.size() < n) {
        addUnique(values, rnd.next(1, 1000000));
    }

    vector<long long> out(values.begin(), values.end());
    shuffle(out.begin(), out.end());
    println((int)out.size());
    for (long long value : out) {
        println(value);
    }

    return 0;
}
