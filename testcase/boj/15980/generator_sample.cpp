#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeRandomBits(int m, int density) {
    string s;
    s.reserve(m);
    for (int i = 0; i < m; ++i) {
        s.push_back(rnd.next(0, 99) < density ? '1' : '0');
    }
    return s;
}

string makePatternBits(int m, int pattern, int shift) {
    string s;
    s.reserve(m);
    for (int i = 0; i < m; ++i) {
        bool bit = false;
        if (pattern == 0) bit = ((i + shift) % 2 == 0);
        if (pattern == 1) bit = ((i + shift) % 3 == 0);
        if (pattern == 2) bit = (i < m / 2);
        if (pattern == 3) bit = (i >= m / 2);
        s.push_back(bit ? '1' : '0');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = rnd.next(1, 18);

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(1, 12);
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 5);
        m = rnd.next(4, 18);
    } else {
        n = rnd.next(3, 10);
        m = rnd.next(2, 20);
    }

    vector<char> side(n);
    vector<string> chirps(n);

    if (mode == 2) {
        for (int i = 0; i < n; i += 2) {
            side[i] = 'L';
            side[i + 1] = 'R';
            string s = makePatternBits(m, rnd.next(0, 3), rnd.next(0, 2));
            chirps[i] = s;
            chirps[i + 1] = s;
            if (rnd.next(0, 2) == 0) {
                int pos = rnd.next(0, m - 1);
                chirps[i + 1][pos] = chirps[i + 1][pos] == '0' ? '1' : '0';
            }
        }
    } else {
        int density = rnd.any(vector<int>{0, 10, 30, 50, 70, 90, 100});
        for (int i = 0; i < n; ++i) {
            side[i] = rnd.next(0, 1) == 0 ? 'L' : 'R';
            if (mode == 1 && i < 2) {
                chirps[i] = string(m, i == 0 ? '0' : '1');
            } else if (mode == 3) {
                chirps[i] = makePatternBits(m, rnd.next(0, 3), rnd.next(0, 2));
            } else {
                chirps[i] = makeRandomBits(m, density);
            }
        }
    }

    shuffle(side.begin(), side.end());
    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(string(1, side[i]), chirps[i]);
    }

    return 0;
}
