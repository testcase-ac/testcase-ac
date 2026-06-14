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

string blockString(const vector<pair<char, int>>& blocks) {
    string s;
    for (auto [ch, len] : blocks) {
        s.append(len, ch);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    string s;

    if (mode == 0) {
        int n = rnd.next(3, 12);
        s = randomString(n, "JOI");
    } else if (mode == 1) {
        int n = rnd.next(3, 30);
        string alphabet = rnd.any(vector<string>{"J", "O", "I", "JO", "OI", "JI"});
        s = randomString(n, alphabet);
    } else if (mode == 2) {
        int j = rnd.next(1, 15);
        int o = rnd.next(1, 15);
        int i = rnd.next(1, 15);
        s = blockString({{'J', j}, {'O', o}, {'I', i}});
    } else if (mode == 3) {
        int n = rnd.next(3, 30);
        string pattern = rnd.any(vector<string>{"JOI", "JIO", "OJI", "IOJ"});
        for (int i = 0; i < n; ++i) {
            s += pattern[i % (int)pattern.size()];
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 30);
        s = randomString(n, "JOI");
        int pos = rnd.next(0, n - 1);
        s[pos] = rnd.any(string("JOI"));
    } else if (mode == 5) {
        int prefix = rnd.next(0, 10);
        int middle = rnd.next(1, 10);
        int suffix = rnd.next(0, 10);
        vector<pair<char, int>> blocks = {
            {rnd.any(string("JOI")), prefix},
            {'O', middle},
            {rnd.any(string("JOI")), suffix},
        };
        s = blockString(blocks);
        while ((int)s.size() < 3) {
            s += rnd.any(string("JOI"));
        }
    } else if (mode == 6) {
        int n = rnd.next(31, 300);
        s = randomString(n, "JOI");
    } else {
        int j = rnd.next(1000, 40000);
        int o = rnd.next(1000, 40000);
        int i = rnd.next(1000, 40000);
        int total = j + o + i;
        if (total > 100000) {
            int excess = total - 100000;
            i = max(1, i - excess);
        }
        s = blockString({{'J', j}, {'O', o}, {'I', i}});
    }

    println((int)s.size());
    println(s);

    return 0;
}
