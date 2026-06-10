#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string makeRamp(int len, bool repeatedHeavy) {
    string s;
    s.reserve(len);

    int digit = rnd.next(1, 9);
    for (int i = 0; i < len; ++i) {
        if (i > 0) {
            int stayWeight = repeatedHeavy ? 5 : 1;
            if (digit < 9 && rnd.next(0, stayWeight) == 0) {
                digit = rnd.next(digit + 1, 9);
            }
        }
        s.push_back(char('0' + digit));
    }

    return s;
}

string makeNonRamp(int len) {
    len = max(len, 2);
    string s;
    s.reserve(len);

    int first = rnd.next(2, 9);
    s.push_back(char('0' + first));

    int forcedDrop = rnd.next(1, len - 1);
    int previous = first;
    for (int i = 1; i < len; ++i) {
        int digit;
        if (i == forcedDrop) {
            digit = rnd.next(0, previous - 1);
        } else if (i < forcedDrop) {
            digit = rnd.next(1, 9);
        } else {
            digit = rnd.next(0, 9);
        }
        s.push_back(char('0' + digit));
        previous = digit;
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> cases;

    int t = rnd.next(12, 30);
    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 6);
        int len;

        if (mode <= 1) {
            len = rnd.next(1, 8);
            cases.push_back(makeRamp(len, mode == 1));
        } else if (mode == 2) {
            len = rnd.next(20, 80);
            cases.push_back(makeRamp(len, true));
        } else if (mode == 3) {
            len = rnd.next(2, 12);
            cases.push_back(makeNonRamp(len));
        } else if (mode == 4) {
            len = rnd.next(30, 80);
            cases.push_back(makeNonRamp(len));
        } else if (mode == 5) {
            len = rnd.next(1, 80);
            cases.push_back(string(len, char('0' + rnd.next(1, 9))));
        } else {
            len = rnd.next(1, 80);
            string s = makeRamp(len, true);
            if (len > 1 && rnd.next(0, 1)) {
                reverse(s.begin(), s.end());
            }
            cases.push_back(s);
        }
    }

    println((int)cases.size());
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
