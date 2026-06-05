#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static string repeatChar(char c, int count) {
    return string(count, c);
}

static void appendRun(string& s, char c, int lo, int hi) {
    s += repeatChar(c, rnd.next(lo, hi));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = repeatChar('R', rnd.next(1, 30));
    } else if (mode == 1) {
        s = repeatChar('K', rnd.next(1, 30));
    } else if (mode == 2) {
        int leftK = rnd.next(0, 10);
        int rightK = rnd.next(0, 10);
        int middleR = rnd.next(1, 20);
        s = repeatChar('K', leftK) + repeatChar('R', middleR) + repeatChar('K', rightK);
    } else if (mode == 3) {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            appendRun(s, 'K', 0, 5);
            appendRun(s, 'R', 1, 5);
        }
        appendRun(s, 'K', 0, 8);
    } else if (mode == 4) {
        int n = rnd.next(1, 40);
        char first = rnd.next(0, 1) == 0 ? 'K' : 'R';
        for (int i = 0; i < n; ++i) {
            s += (i % 2 == 0 ? first : (first == 'K' ? 'R' : 'K'));
        }
    } else {
        int n = rnd.next(1, 60);
        int kBias = rnd.next(15, 85);
        for (int i = 0; i < n; ++i) {
            s += rnd.next(1, 100) <= kBias ? 'K' : 'R';
        }
    }

    if (rnd.next(0, 3) == 0 && s.size() > 1) {
        reverse(s.begin(), s.end());
    }

    println(s);
    return 0;
}
