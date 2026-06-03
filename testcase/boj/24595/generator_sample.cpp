#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomDigits(int len) {
    string s;
    s.reserve(len);
    s.push_back(char('1' + rnd.next(9)));
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(10)));
    }
    return s;
}

string monotoneDigits(int len, bool nondecreasing) {
    vector<int> cuts(10, 0);
    for (int i = 0; i < len; ++i) {
        ++cuts[rnd.next(10)];
    }

    string s;
    s.reserve(len);
    if (nondecreasing) {
        for (int d = 0; d <= 9; ++d) {
            s.append(cuts[d], char('0' + d));
        }
        if (s[0] == '0') {
            int pos = 0;
            while (pos < len && s[pos] == '0') ++pos;
            if (pos == len) s.back() = '1';
            else swap(s[0], s[pos]);
        }
    } else {
        for (int d = 9; d >= 0; --d) {
            s.append(cuts[d], char('0' + d));
        }
    }
    return s;
}

string riseAndFallDigits(int len) {
    int peak = rnd.next(0, len - 1);
    string left = monotoneDigits(peak + 1, true);
    string right = monotoneDigits(len - peak - 1, false);
    return left + right;
}

string valleyThenRise(int len) {
    int high = rnd.next(2, 9);
    int low = rnd.next(0, high - 1);
    int rebound = rnd.next(low + 1, high);

    string s;
    s.reserve(len);
    s.push_back(char('0' + high));
    int valleyLen = rnd.next(1, max(1, len - 2));
    for (int i = 0; i < valleyLen && static_cast<int>(s.size()) < len; ++i) {
        s.push_back(char('0' + rnd.next(low, high - 1)));
    }
    if (static_cast<int>(s.size()) < len) {
        s.push_back(char('0' + rebound));
    }
    while (static_cast<int>(s.size()) < len) {
        s.push_back(char('0' + rnd.next(rebound, 9)));
    }
    return s;
}

string plateauTrap(int len) {
    int a = rnd.next(1, 8);
    int b = rnd.next(0, a - 1);
    int c = rnd.next(b + 1, 9);
    string s;
    s.reserve(len);
    int first = rnd.next(1, max(1, len / 3));
    int second = rnd.next(1, max(1, len / 3));
    s.append(first, char('0' + a));
    s.append(second, char('0' + b));
    while (static_cast<int>(s.size()) < len) {
        s.push_back(char('0' + rnd.next(c, 9)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 24);
    vector<string> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(8);
        int len = 1;
        if (mode <= 1) len = rnd.next(1, 4);
        else if (mode <= 5) len = rnd.next(2, 18);
        else len = rnd.next(8, 30);

        if (mode == 0) {
            cases.push_back(to_string(rnd.next(1, 9)));
        } else if (mode == 1) {
            cases.push_back(randomDigits(len));
        } else if (mode == 2) {
            cases.push_back(monotoneDigits(len, true));
        } else if (mode == 3) {
            cases.push_back(monotoneDigits(len, false));
        } else if (mode == 4) {
            cases.push_back(riseAndFallDigits(len));
        } else if (mode == 5) {
            cases.push_back(valleyThenRise(len));
        } else if (mode == 6) {
            cases.push_back(plateauTrap(len));
        } else {
            cases.push_back(randomDigits(len));
        }
    }

    println(static_cast<int>(cases.size()));
    for (const string& n : cases) {
        println(n);
    }

    return 0;
}
