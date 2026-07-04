#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

string repeatPattern(const string& pattern, int length) {
    string s;
    while ((int)s.size() < length) {
        s += pattern;
    }
    s.resize(length);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int length;
    string s;

    if (mode == 0) {
        length = rnd.next(1, 5);
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < length; ++i) {
            s += rnd.any(alphabet);
        }
    } else if (mode == 1) {
        length = rnd.any(vector<int>{1, 2, 3, 5, 49, 50});
        char c = rnd.any(string("az"));
        s.assign(length, c);
    } else if (mode == 2) {
        length = rnd.next(6, 30);
        string pattern = rnd.any(vector<string>{"ab", "ba", "az", "za", "abc", "zzzaz"});
        s = repeatPattern(pattern, length);
    } else if (mode == 3) {
        length = rnd.next(20, 50);
        int maxLetter = rnd.next(1, 26);
        for (int i = 0; i < length; ++i) {
            s += char('a' + rnd.next(0, maxLetter - 1));
        }
    } else if (mode == 4) {
        length = rnd.next(10, 50);
        for (int i = 0; i < length; ++i) {
            s += char('a' + (i % 26));
        }
        if (rnd.next(0, 1) == 1) {
            reverse(s.begin(), s.end());
        }
    } else if (mode == 5) {
        length = rnd.next(2, 50);
        s.assign(length, 'a');
        int changes = rnd.next(1, min(length, 8));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, length - 1);
            s[pos] = rnd.any(string("bcxyz"));
        }
    } else {
        length = rnd.next(1, 50);
        string letters = "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < length; ++i) {
            s += rnd.any(letters);
        }
    }

    println(length);
    println(s);

    return 0;
}
