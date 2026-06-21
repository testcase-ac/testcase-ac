#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 80);
    int k = rnd.next(2, n - 1);
    string s(n, 'O');

    if (mode == 0) {
        k = rnd.next(2, min(8, n - 1));
        int groups = rnd.next(1, max(1, min(5, n / (k + 1))));
        string block;
        for (int g = 0; g < groups; ++g) {
            block += 'R';
            block += string(k, 'O');
        }
        n = rnd.next(max(3, (int)block.size()), min(80, max(3, (int)block.size() + 20)));
        s.assign(n, rnd.next(0, 1) ? 'O' : 'R');
        int start = rnd.next(0, n - (int)block.size());
        for (int i = 0; i < (int)block.size(); ++i) s[start + i] = block[i];
    } else if (mode == 1) {
        k = rnd.next(2, min(12, n - 1));
        for (int i = 0; i < n; ++i) {
            int phase = i % (k + 1);
            s[i] = (phase == 0 ? 'R' : 'O');
        }
        int edits = rnd.next(0, min(8, n));
        for (int i = 0; i < edits; ++i) {
            int pos = rnd.next(0, n - 1);
            s[pos] = (s[pos] == 'O' ? 'R' : 'O');
        }
    } else if (mode == 2) {
        k = rnd.next(max(2, n / 2), n - 1);
        int tails = rnd.next(0, 2);
        s.assign(n, 'O');
        for (int i = 0; i < tails; ++i) s[rnd.next(0, n - 1)] = 'R';
    } else if (mode == 3) {
        k = rnd.next(2, min(10, n - 1));
        s.clear();
        while ((int)s.size() < n) {
            char c = rnd.next(0, 1) ? 'O' : 'R';
            int len = rnd.next(1, min(12, n - (int)s.size()));
            s += string(len, c);
        }
    } else if (mode == 4) {
        k = rnd.next(2, min(15, n - 1));
        int oCount = rnd.next(0, n);
        s.assign(oCount, 'O');
        s += string(n - oCount, 'R');
        shuffle(s.begin(), s.end());
    } else {
        n = rnd.next(3, 25);
        k = rnd.next(2, n - 1);
        s.resize(n);
        for (int i = 0; i < n; ++i) s[i] = rnd.next(0, 1) ? 'O' : 'R';
    }

    println(n, k);
    println(s);
    return 0;
}
