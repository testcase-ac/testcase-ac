#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    string wheel;
    string target;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 20);
        char c = char('a' + rnd.next(0, 25));
        wheel = string(1, c);
        target.assign(m, rnd.next(0, 3) == 0 ? char('a' + rnd.next(0, 25)) : c);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        m = rnd.next(1, 30);
        char common = char('a' + rnd.next(0, 25));
        wheel.assign(n, common);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                wheel[i] = char('a' + rnd.next(0, 25));
            }
        }
        for (int i = 0; i < m; ++i) {
            target += rnd.next(0, 1) == 0 ? common : wheel[rnd.next(0, n - 1)];
        }
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        m = rnd.next(1, 25);
        int alphabet = rnd.next(1, min(6, n));
        for (int i = 0; i < n; ++i) {
            wheel += char('a' + rnd.next(0, alphabet - 1));
        }
        char absent = char('z' - rnd.next(0, 3));
        while (wheel.find(absent) != string::npos) {
            absent = char('a' + rnd.next(0, 25));
        }
        for (int i = 0; i < m; ++i) {
            target += rnd.next(0, 4) == 0 ? absent : wheel[rnd.next(0, n - 1)];
        }
    } else if (mode == 3) {
        n = rnd.next(2, 26);
        m = rnd.next(10, 45);
        vector<char> letters;
        for (char c = 'a'; c <= 'z'; ++c) {
            letters.push_back(c);
        }
        shuffle(letters.begin(), letters.end());
        for (int i = 0; i < n; ++i) {
            wheel += letters[i % (int)letters.size()];
        }
        for (int i = 0; i < m; ++i) {
            target += wheel[rnd.next(0, n - 1)];
        }
    } else if (mode == 4) {
        n = rnd.next(12, 35);
        m = rnd.next(20, 60);
        int alphabet = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            wheel += char('a' + rnd.next(0, alphabet - 1));
        }
        int pos = rnd.next(0, n - 1);
        for (int i = 0; i < m; ++i) {
            pos = (pos + rnd.next(1, max(1, n / 2))) % n;
            target += wheel[pos];
        }
    } else {
        n = rnd.next(60, 100);
        m = rnd.next(60, 100);
        int alphabet = rnd.next(1, 26);
        for (int i = 0; i < n; ++i) {
            wheel += char('a' + rnd.next(0, alphabet - 1));
        }
        for (int i = 0; i < m; ++i) {
            target += wheel[rnd.next(0, n - 1)];
        }
    }

    println(n);
    println(wheel);
    println(m);
    println(target);

    return 0;
}
