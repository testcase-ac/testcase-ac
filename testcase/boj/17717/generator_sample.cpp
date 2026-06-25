#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string makeLevel(int k) {
    if (k == 0) {
        const string alphabet = "JOI";
        return string(1, rnd.any(alphabet));
    }

    string prev = makeLevel(k - 1);
    string block(prev.size(), 'J');
    string result = block;
    block.assign(prev.size(), 'O');
    result += block;
    block.assign(prev.size(), 'I');
    result += block;
    result += prev;
    return result;
}

void mutate(string& s, int changes) {
    const string alphabet = "JOI";
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next((int)s.size());
        char c = rnd.any(alphabet);
        while (c == s[pos]) c = rnd.any(alphabet);
        s[pos] = c;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = rnd.next(1, 5);
    if (rnd.next(100) < 8) k = rnd.next(6, 10);

    int n = 1;
    for (int i = 0; i < k; ++i) n *= 4;

    const string alphabet = "JOI";
    string s;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    } else if (mode == 1) {
        s.assign(n, rnd.any(alphabet));
        mutate(s, rnd.next(0, min(n, 12)));
    } else if (mode == 2) {
        int period = rnd.next(1, min(n, 12));
        string pattern;
        for (int i = 0; i < period; ++i) pattern += rnd.any(alphabet);
        for (int i = 0; i < n; ++i) s += pattern[i % period];
    } else if (mode == 3) {
        s = makeLevel(k);
        rotate(s.begin(), s.begin() + rnd.next(n), s.end());
        mutate(s, rnd.next(0, min(n, 20)));
    } else if (mode == 4) {
        int block = n / 4;
        vector<char> chars = {'J', 'O', 'I', rnd.any(alphabet)};
        if (rnd.next(2)) shuffle(chars.begin(), chars.end());
        for (char c : chars) s += string(block, c);
        mutate(s, rnd.next(0, min(n, 16)));
    } else {
        int block = 1;
        for (int i = 0; i < rnd.next(0, k); ++i) block *= 4;
        while ((int)s.size() < n) {
            char c = rnd.any(alphabet);
            int len = min(block * rnd.next(1, 4), n - (int)s.size());
            s += string(len, c);
        }
    }

    println(k);
    println(s);
    return 0;
}
