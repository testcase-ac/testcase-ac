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

string repeatToLength(const string& pattern, int n) {
    string s;
    s.reserve(n);
    while ((int)s.size() < n) {
        s += pattern;
    }
    s.resize(n);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> seeds = {"a", "ab", "aba", "abc", "abcd", "qwerty", "prefix", "pap"};
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    const int mode = rnd.next(0, 7);

    string s;
    if (mode == 0) {
        s = randomString(rnd.next(1, 8), alphabet.substr(0, rnd.next(1, 4)));
    } else if (mode == 1) {
        s = string(rnd.next(1, 45), rnd.any(alphabet));
    } else if (mode == 2) {
        string pattern = rnd.any(seeds);
        s = repeatToLength(pattern, rnd.next((int)pattern.size(), min(60, (int)pattern.size() * rnd.next(2, 8))));
    } else if (mode == 3) {
        string border = rnd.any(seeds);
        string middle = randomString(rnd.next(1, 12), alphabet.substr(0, rnd.next(2, 7)));
        s = border + middle + border + randomString(rnd.next(0, 5), alphabet) + border;
    } else if (mode == 4) {
        string border = rnd.any(seeds);
        char filler = rnd.next(0, 1) ? 'x' : 'z';
        if (border.find(filler) != string::npos) {
            filler = 'y';
        }
        s = border + string(rnd.next(1, 25), filler) + border;
    } else if (mode == 5) {
        string block = rnd.any(seeds);
        string tail = block.substr(0, rnd.next(1, (int)block.size()));
        s = block + randomString(rnd.next(0, 8), "abc") + block + tail;
    } else if (mode == 6) {
        string pattern = randomString(rnd.next(1, 5), alphabet.substr(0, rnd.next(1, 3)));
        s = repeatToLength(pattern, rnd.next(20, 80));
    } else {
        s = randomString(rnd.next(10, 70), alphabet.substr(0, rnd.next(2, 26)));
    }

    println(s);
    return 0;
}
