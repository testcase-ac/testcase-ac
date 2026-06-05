#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

char nextColor(char c) {
    if (c == 'R') return 'G';
    if (c == 'G') return 'B';
    return 'R';
}

void advanceTriple(string& s, int pos, int count) {
    for (int step = 0; step < count; ++step) {
        for (int i = 0; i < 3; ++i) {
            s[pos + i] = nextColor(s[pos + i]);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string colors = "RGB";
    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 30);
    string s;

    if (mode == 0) {
        s.assign(n, rnd.any(colors));
    } else if (mode == 1) {
        s.resize(n);
        for (int i = 0; i < n; ++i) {
            s[i] = colors[i % 3];
        }
        int shift = rnd.next(0, 2);
        for (char& c : s) {
            for (int j = 0; j < shift; ++j) c = nextColor(c);
        }
    } else if (mode == 2) {
        s.resize(n);
        for (char& c : s) c = rnd.any(colors);
    } else if (mode == 3) {
        s.assign(n, rnd.any(colors));
        int operations = rnd.next(1, 2 * n);
        for (int i = 0; i < operations; ++i) {
            advanceTriple(s, rnd.next(0, n - 3), rnd.next(1, 2));
        }
    } else if (mode == 4) {
        vector<string> blocks = {"RRG", "RGB", "BRR", "GBB", "BGR"};
        while ((int)s.size() < n) {
            s += rnd.any(blocks);
        }
        s.resize(n);
    } else {
        n = rnd.next(3, 100);
        s.resize(n);
        char previous = rnd.any(colors);
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rnd.next(0, 99) < 65) {
                previous = rnd.any(colors);
            }
            s[i] = previous;
        }
    }

    println(n);
    println(s);

    return 0;
}
