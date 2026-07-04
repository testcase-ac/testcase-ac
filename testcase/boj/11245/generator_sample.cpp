#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int randomLength() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 1;
    if (mode == 1) return rnd.next(2, 30);
    if (mode == 2) return rnd.next(31, 500);
    if (mode == 3) return rnd.next(501, 5000);
    return rnd.next(90000, 100000);
}

vector<vector<int>> makeTable(int mode) {
    vector<vector<int>> s(26, vector<int>(26, 0));

    if (mode == 0) {
        int hi = rnd.next(1, 100);
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                s[i][j] = rnd.next(0, hi);
            }
        }
    } else if (mode == 1) {
        int base = rnd.next(0, 80);
        int bonus = rnd.next(5, 20);
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                s[i][j] = max(0, min(100, base + rnd.next(-5, 5)));
            }
            s[i][i] = min(100, base + bonus + rnd.next(0, 10));
        }
    } else if (mode == 2) {
        int cycleLen = rnd.next(2, 8);
        vector<int> notes(26);
        for (int i = 0; i < 26; ++i) notes[i] = i;
        shuffle(notes.begin(), notes.end());
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                s[i][j] = rnd.next(0, 4);
            }
        }
        for (int i = 0; i < cycleLen; ++i) {
            int from = notes[i];
            int to = notes[(i + 1) % cycleLen];
            s[from][to] = rnd.next(85, 100);
        }
    } else if (mode == 3) {
        int special = rnd.next(0, 25);
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                s[i][j] = rnd.next(0, 8);
            }
            s[i][special] = rnd.next(70, 100);
            s[special][i] = rnd.next(40, 100);
        }
    } else {
        int fill = rnd.next(0, 100);
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                s[i][j] = fill;
            }
        }
        for (int k = 0; k < rnd.next(3, 20); ++k) {
            s[rnd.next(0, 25)][rnd.next(0, 25)] = rnd.next(0, 100);
        }
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        vector<vector<int>> s = makeTable(rnd.next(0, 4));
        for (int i = 0; i < 26; ++i) {
            println(s[i]);
        }

        int n = rnd.next(1, 10);
        println(n);

        vector<char> starts;
        starts.push_back('A');
        starts.push_back('Z');
        while ((int)starts.size() < n) {
            starts.push_back(char('A' + rnd.next(0, 25)));
        }
        shuffle(starts.begin(), starts.end());

        for (int i = 0; i < n; ++i) {
            int len = (i == 0 && rnd.next(0, 1) == 0) ? 1 : randomLength();
            println(string(1, starts[i]), len);
        }
    }

    return 0;
}
