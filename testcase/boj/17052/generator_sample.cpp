#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 30);
    } else if (mode == 3) {
        n = rnd.next(90, 100);
    } else {
        n = rnd.next(1, 100);
    }

    string s(n, '0');
    for (int i = 0; i < n; ++i) {
        s[i] = char('0' + rnd.next(0, 9));
    }

    int xPos = 0;
    if (n == 1) {
        xPos = 0;
    } else if (mode == 1) {
        xPos = n - 1;
    } else if (mode == 2) {
        vector<int> doubled;
        for (int i = 0; i < n - 1; ++i) {
            if (((n - 1 - i) & 1) == 1) {
                doubled.push_back(i);
            }
        }
        xPos = rnd.any(doubled);
    } else if (mode == 3) {
        vector<int> plain;
        for (int i = 0; i < n - 1; ++i) {
            if (((n - 1 - i) & 1) == 0) {
                plain.push_back(i);
            }
        }
        xPos = plain.empty() ? n - 1 : rnd.any(plain);
    } else {
        xPos = rnd.next(0, n - 1);
    }
    s[xPos] = 'x';

    println(n);
    println(s);

    return 0;
}
