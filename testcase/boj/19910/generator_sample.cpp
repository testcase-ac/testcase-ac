#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string alternatingBlocks(int blocks, int maxRun) {
    string s;
    char ch = rnd.next(0, 1) == 0 ? '0' : '1';
    for (int i = 0; i < blocks; ++i) {
        int len = rnd.next(1, maxRun);
        s.append(len, ch);
        ch = ch == '0' ? '1' : '0';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = string(rnd.next(1, 24), '1');
    } else if (mode == 1) {
        int leftZeros = rnd.next(0, 12);
        int rightZeros = rnd.next(0, 12);
        s = string(leftZeros, '0') + "1" + string(rightZeros, '0');
    } else if (mode == 2) {
        int flags = rnd.next(2, 12);
        int gap = rnd.next(0, 5);
        for (int i = 0; i < flags; ++i) {
            if (i > 0) s.append(gap, '0');
            s.push_back('1');
        }
    } else if (mode == 3) {
        s = alternatingBlocks(rnd.next(2, 12), rnd.next(1, 5));
    } else if (mode == 4) {
        int n = rnd.next(2, 40);
        double oneProbability = rnd.next(0.10, 0.90);
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next() < oneProbability ? '1' : '0');
        }
    } else {
        int n = rnd.next(20, 120);
        s.assign(n, '0');
        int ones = rnd.next(1, min(n, 16));
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < ones; ++i) s[positions[i]] = '1';
    }

    if (count(s.begin(), s.end(), '1') == 0) {
        s[rnd.next(0, (int)s.size() - 1)] = '1';
    }

    println((int)s.size());
    println(s);

    return 0;
}
