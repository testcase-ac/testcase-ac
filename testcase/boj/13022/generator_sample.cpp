#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string block(int n) {
    return string(n, 'w') + string(n, 'o') + string(n, 'l') + string(n, 'f');
}

string validWord(int maxLength) {
    string s;
    while (s.empty() || (int)s.size() + 4 <= maxLength) {
        int remainingBlocks = (maxLength - (int)s.size()) / 4;
        int n = rnd.next(1, remainingBlocks);
        s += block(n);
        if (rnd.next(0, 2) == 0) break;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = validWord(50);
    } else if (mode == 1) {
        int n = rnd.next(1, 12);
        vector<int> cnt = {n, n, n, n};
        int pos = rnd.next(0, 3);
        cnt[pos] += rnd.next(1, min(3, 50 - 4 * n));
        s = string(cnt[0], 'w') + string(cnt[1], 'o') + string(cnt[2], 'l') + string(cnt[3], 'f');
    } else if (mode == 2) {
        s = validWord(40);
        int insertAt = rnd.next(0, (int)s.size());
        char c = rnd.any(string("wolf"));
        s.insert(s.begin() + insertAt, c);
    } else if (mode == 3) {
        int len = rnd.next(1, 50);
        for (int i = 0; i < len; ++i) s += rnd.any(string("wolf"));
    } else if (mode == 4) {
        int n = rnd.next(1, 12);
        s = string(n, 'w') + string(n, 'f') + string(n, 'o') + string(n, 'l');
    } else {
        s = block(12);
        if (rnd.next(0, 1) == 0) {
            s += rnd.any(string("wo"));
        } else {
            int eraseAt = rnd.next(0, (int)s.size() - 1);
            s.erase(s.begin() + eraseAt);
        }
    }

    println(s);
    return 0;
}
