#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string digits(int len, bool nonzeroFirst) {
    string s;
    s.reserve(len);
    if (nonzeroFirst) {
        s.push_back(char('1' + rnd.next(9)));
    } else {
        s.push_back(char('0' + rnd.next(10)));
    }
    for (int i = 1; i < len; ++i) {
        s.push_back(char('0' + rnd.next(10)));
    }
    return s;
}

string repeatedPattern(const string& pattern, int repeats, int extra) {
    string s;
    for (int i = 0; i < repeats; ++i) {
        s += pattern;
    }
    s += pattern.substr(0, extra);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> parts;
    int mode = rnd.next(5);

    if (mode == 0) {
        parts.push_back(digits(rnd.next(1, 30), true));
    } else if (mode == 1) {
        int n = rnd.next(3, 12);
        int good = rnd.next(n);
        for (int i = 0; i < n; ++i) {
            int zeroes = i == good ? 0 : rnd.next(0, 6);
            string s(zeroes, '0');
            s += digits(rnd.next(1, 12), i == good);
            if (i != good && rnd.next(2) == 0) {
                s[0] = '0';
            }
            parts.push_back(s);
        }
    } else if (mode == 2) {
        vector<string> bases = {"12", "34", "56", "78", "90", "121", "343", "565"};
        string base = rnd.any(bases);
        int n = rnd.next(4, 14);
        for (int i = 0; i < n; ++i) {
            int repeats = rnd.next(1, 4);
            int extra = rnd.next((int)base.size());
            parts.push_back(repeatedPattern(base, repeats, extra));
        }
    } else if (mode == 3) {
        int n = rnd.next(4, 20);
        for (int i = 0; i < n; ++i) {
            char d = char('0' + rnd.next(10));
            int len = rnd.next(1, 24);
            string s(len, d);
            if (i == 0 && d == '0') {
                s[0] = char('1' + rnd.next(9));
            }
            parts.push_back(s);
        }
    } else {
        int n = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 4);
            bool nonzeroFirst = i == 0 || rnd.next(4) != 0;
            parts.push_back(digits(len, nonzeroFirst));
        }
    }

    shuffle(parts.begin(), parts.end());
    for (const string& part : parts) {
        println(part);
    }

    return 0;
}
