#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomBalanced(int pairs) {
    string s;
    int opened = 0;
    int closed = 0;
    while (closed < pairs) {
        if (opened == pairs) {
            s += ')';
            ++closed;
        } else if (opened == closed || rnd.next(2) == 0) {
            s += '(';
            ++opened;
        } else {
            s += ')';
            ++closed;
        }
    }
    return s;
}

string alternating(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += (i % 2 == 0 ? '(' : ')');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    string s;

    if (mode == 0) {
        int pairs = rnd.next(1, 12);
        s = randomBalanced(pairs);
        int pos = rnd.next((int)s.size());
        s[pos] = (s[pos] == '(' ? ')' : '(');
    } else if (mode == 1) {
        int pairs = rnd.next(1, 12);
        s = randomBalanced(pairs);
    } else if (mode == 2) {
        int n = rnd.next(1, 25);
        int opens = rnd.next(0, n);
        s = string(opens, '(') + string(n - opens, ')');
    } else if (mode == 3) {
        int n = rnd.next(1, 25);
        s = alternating(n);
        if (rnd.next(2) == 0) reverse(s.begin(), s.end());
    } else if (mode == 4) {
        int n = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            s += (rnd.next(100) < 55 ? '(' : ')');
        }
    } else if (mode == 5) {
        int n = rnd.next(2, 25);
        s = string(n, rnd.next(2) == 0 ? '(' : ')');
    } else {
        int pairs = rnd.next(1, 10);
        s = randomBalanced(pairs);
        vector<int> positions((int)s.size());
        for (int i = 0; i < (int)positions.size(); ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        int flips = rnd.next(1, min(4, (int)s.size()));
        for (int i = 0; i < flips; ++i) {
            int pos = positions[i];
            s[pos] = (s[pos] == '(' ? ')' : '(');
        }
    }

    println(s);
    return 0;
}
