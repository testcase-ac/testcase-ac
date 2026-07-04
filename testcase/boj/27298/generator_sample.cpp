#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static char digit() {
    return char('1' + rnd.next(0, 8));
}

static int length() {
    int mode = rnd.next(0, 9);
    if (mode <= 5) return rnd.next(1, 30);
    if (mode <= 7) return rnd.next(31, 200);
    if (mode == 8) return rnd.next(201, 500);
    return rnd.any(vector<int>{9998, 9999, 10000});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = length();
    int mode = rnd.next(0, 6);
    string s(n, '1');

    if (mode == 0) {
        fill(s.begin(), s.end(), digit());
    } else if (mode == 1) {
        char a = digit();
        char b = digit();
        while (b == a) b = digit();
        for (int i = 0; i < n; ++i) s[i] = (i % 2 == 0 ? a : b);
    } else if (mode == 2) {
        int block = rnd.next(1, min(n, 20));
        for (int i = 0; i < n; ++i) {
            if (i % block == 0) s[i] = digit();
            else s[i] = s[i - 1];
        }
    } else if (mode == 3) {
        for (int i = 0; i < (n + 1) / 2; ++i) {
            s[i] = digit();
            s[n - 1 - i] = s[i];
        }
    } else if (mode == 4) {
        string pool = rnd.any(vector<string>{"13579", "2468", "123", "789", "159"});
        for (int i = 0; i < n; ++i) s[i] = rnd.any(pool);
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) s[i] = digit();
        int repeats = rnd.next(1, min(n, 12));
        char d = digit();
        for (int i = 0; i < repeats; ++i) s[rnd.next(0, n - 1)] = d;
    } else {
        for (int i = 0; i < n; ++i) s[i] = digit();
    }

    println(s);
    return 0;
}
