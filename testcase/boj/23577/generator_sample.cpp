#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeValue(int a, int b, int c, int d) {
    string value;
    value += char('0' + a);
    value += char('0' + b);
    value += char('0' + c);
    value += char('0' + d);
    return value;
}

void addValue(vector<string>& values, set<string>& seen, const string& value) {
    if (seen.insert(value).second) {
        values.push_back(value);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> values;
    set<string> seen;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 18);
        while ((int)values.size() < n) {
            addValue(values, seen, makeValue(rnd.next(1, 9), rnd.next(1, 9), rnd.next(1, 9), rnd.next(1, 9)));
        }
    } else if (mode == 1) {
        vector<string> all;
        for (int a = 1; a <= 9; ++a)
            for (int b = 1; b <= 9; ++b)
                for (int c = 1; c <= 9; ++c)
                    for (int d = 1; d <= 9; ++d)
                        all.push_back(makeValue(a, b, c, d));

        shuffle(all.begin(), all.end());
        int n = rnd.next(25, 120);
        values.assign(all.begin(), all.begin() + n);
    } else if (mode == 2) {
        int first = rnd.next(1, 9);
        int n = rnd.next(8, 50);
        while ((int)values.size() < n) {
            addValue(values, seen, makeValue(first, rnd.next(1, 9), rnd.next(1, 9), rnd.next(1, 9)));
        }
    } else if (mode == 3) {
        int first = rnd.next(1, 9);
        int second = rnd.next(1, 9);
        int n = rnd.next(8, 40);
        while ((int)values.size() < n) {
            addValue(values, seen, makeValue(first, second, rnd.next(1, 9), rnd.next(1, 9)));
        }
    } else if (mode == 4) {
        int shift1 = rnd.next(0, 8);
        int shift2 = rnd.next(0, 8);
        int shift3 = rnd.next(0, 8);
        int n = rnd.next(9, 45);
        for (int i = 0; i < n; ++i) {
            int x = i % 9;
            addValue(values, seen, makeValue(x + 1, (x + shift1) % 9 + 1, (x + shift2) % 9 + 1, (x + shift3) % 9 + 1));
        }
    } else {
        int baseA = rnd.next(1, 9);
        int baseB = rnd.next(1, 9);
        int baseC = rnd.next(1, 9);
        int baseD = rnd.next(1, 9);
        addValue(values, seen, makeValue(baseA, baseB, baseC, baseD));

        int n = rnd.next(6, 32);
        while ((int)values.size() < n) {
            int pos = rnd.next(0, 3);
            int digits[4] = {baseA, baseB, baseC, baseD};
            digits[pos] = rnd.next(1, 9);
            addValue(values, seen, makeValue(digits[0], digits[1], digits[2], digits[3]));
        }
    }

    shuffle(values.begin(), values.end());
    println((int)values.size());
    for (const string& value : values) {
        println(value);
    }

    return 0;
}
