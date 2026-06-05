#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 30);
    string s;

    if (mode == 0) {
        s.assign(n, rnd.next(0, 1) ? 'G' : 'H');
    } else if (mode == 1) {
        char first = rnd.next(0, 1) ? 'G' : 'H';
        for (int i = 0; i < n; ++i) {
            s += (i % 2 == 0) ? first : (first == 'G' ? 'H' : 'G');
        }
    } else if (mode == 2) {
        char solo = rnd.next(0, 1) ? 'G' : 'H';
        char other = solo == 'G' ? 'H' : 'G';
        s.assign(n, other);
        int count = rnd.next(1, min(3, n));
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < count; ++i) s[positions[i]] = solo;
    } else if (mode == 3) {
        char a = rnd.next(0, 1) ? 'G' : 'H';
        char b = a == 'G' ? 'H' : 'G';
        while ((int)s.size() < n) {
            int run = rnd.next(1, min(8, n - (int)s.size()));
            s.append(run, ((int)s.size() == 0 || s.back() == b) ? a : b);
        }
    } else if (mode == 4) {
        char rare = rnd.next(0, 1) ? 'G' : 'H';
        int rarePercent = rnd.next(10, 35);
        for (int i = 0; i < n; ++i) {
            s += rnd.next(1, 100) <= rarePercent ? rare : (rare == 'G' ? 'H' : 'G');
        }
    } else {
        vector<string> blocks;
        char c = rnd.next(0, 1) ? 'G' : 'H';
        int remaining = n;
        while (remaining > 0) {
            int run = rnd.next(1, min(5, remaining));
            blocks.push_back(string(run, c));
            c = c == 'G' ? 'H' : 'G';
            remaining -= run;
        }
        shuffle(blocks.begin(), blocks.end());
        for (const string& block : blocks) s += block;
    }

    println((int)s.size());
    println(s);
    return 0;
}
