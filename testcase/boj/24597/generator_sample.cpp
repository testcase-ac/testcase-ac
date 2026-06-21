#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 3);
        s = randomString(n, "abc");
    } else if (mode == 1) {
        int n = rnd.next(1, 30);
        s.assign(n, char('a' + rnd.next(0, 25)));
    } else if (mode == 2) {
        int n = rnd.next(2, 30);
        string alphabet = "ab";
        s = randomString(n, alphabet);
    } else if (mode == 3) {
        int n = rnd.next(3, 30);
        s = randomString((n + 1) / 2, "abcde");
        string tail = s.substr(0, n / 2);
        reverse(tail.begin(), tail.end());
        s += tail;
        if (rnd.next(0, 1)) {
            s[rnd.next(0, n - 1)] = char('a' + rnd.next(0, 25));
        }
    } else if (mode == 4) {
        int period = rnd.next(1, 6);
        int repeats = rnd.next(2, 8);
        string base = randomString(period, "abcdef");
        for (int i = 0; i < repeats; ++i) {
            s += base;
        }
        if (rnd.next(0, 1) && (int)s.size() < 30) {
            s += base.substr(0, rnd.next(1, period));
        }
    } else if (mode == 5) {
        int n = rnd.next(4, 30);
        s = randomString(n, "abcdefghijklmnopqrstuvwxyz");
    } else if (mode == 6) {
        int n = rnd.next(4, 26);
        vector<char> letters;
        for (char c = 'a'; c <= 'z'; ++c) {
            letters.push_back(c);
        }
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < n; ++i) {
            s += letters[i];
        }
    } else {
        int n = rnd.next(5, 30);
        string block = randomString(rnd.next(1, 5), "abc");
        s = randomString(n, "defgh");
        int pos = rnd.next(0, n - (int)block.size());
        s.replace(pos, block.size(), block);
        if (pos + (int)block.size() < n) {
            string reversed = block;
            reverse(reversed.begin(), reversed.end());
            int pos2 = rnd.next(pos + (int)block.size(), n - 1);
            s[pos2] = reversed[0];
        }
    }

    println(s);
    return 0;
}
