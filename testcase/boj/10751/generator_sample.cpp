#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string repeated(char ch, int count) {
    return string(count, ch);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 30);
    string s;

    if (mode == 0) {
        int c = rnd.next(0, n);
        int o = rnd.next(0, n - c);
        int w = n - c - o;
        s = repeated('C', c) + repeated('O', o) + repeated('W', w);
    } else if (mode == 1) {
        vector<char> pattern = {'C', 'O', 'W'};
        int offset = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            s += pattern[(i + offset) % 3];
        }
    } else if (mode == 2) {
        string alphabet = rnd.any(vector<string>{"C", "O", "W", "CO", "CW", "OW"});
        for (int i = 0; i < n; ++i) {
            s += rnd.any(alphabet);
        }
    } else if (mode == 3) {
        int c = rnd.next(1, max(1, n / 2));
        int w = rnd.next(1, max(1, n - c));
        int o = n - c - w;
        if (o < 0) {
            o = 0;
            w = n - c;
        }
        s = repeated('W', w) + repeated('O', o) + repeated('C', c);
    } else if (mode == 4) {
        int pivot = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i < pivot) {
                s += rnd.any(string("CO"));
            } else {
                s += rnd.any(string("OW"));
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            s += rnd.any(string("COW"));
        }
        sort(s.begin(), s.end());
        shuffle(s.begin(), s.end());
    } else if (mode == 6) {
        n = rnd.next(31, 120);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 99);
            if (bucket < 45) {
                s += 'C';
            } else if (bucket < 70) {
                s += 'O';
            } else {
                s += 'W';
            }
        }
    } else {
        n = rnd.next(1, 100);
        int c = rnd.next(0, n);
        int o = rnd.next(0, n - c);
        int w = n - c - o;
        s = repeated('C', c) + repeated('O', o) + repeated('W', w);
        shuffle(s.begin(), s.end());
    }

    println((int)s.size());
    println(s);
    return 0;
}
