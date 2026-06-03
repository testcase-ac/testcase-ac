#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static char randomLower() {
    return char('a' + rnd.next(26));
}

static string randomString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomLower());
    }
    return s;
}

static void putWindow(string& s, int pos, int mismatches) {
    const string target = "eagle";
    vector<int> idx = {0, 1, 2, 3, 4};
    shuffle(idx.begin(), idx.end());

    for (int i = 0; i < 5; ++i) {
        s[pos + i] = target[i];
    }
    for (int i = 0; i < mismatches; ++i) {
        char c = randomLower();
        while (c == target[idx[i]]) {
            c = randomLower();
        }
        s[pos + idx[i]] = c;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(5, 30);
    string s;

    if (mode == 0) {
        n = rnd.next(5, 20);
        s = randomString(n);
        putWindow(s, rnd.next(0, n - 5), rnd.next(0, 2));
    } else if (mode == 1) {
        n = rnd.next(5, 20);
        s = randomString(n);
        putWindow(s, rnd.next(0, n - 5), rnd.next(3, 5));
    } else if (mode == 2) {
        n = rnd.next(5, 100);
        char fill = randomLower();
        s.assign(n, fill);
        if (rnd.next(2) == 1) {
            putWindow(s, rnd.next(0, n - 5), rnd.next(1, 4));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 35);
        s = randomString(n);
        int windows = rnd.next(1, min(6, n - 4));
        for (int i = 0; i < windows; ++i) {
            putWindow(s, rnd.next(0, n - 5), rnd.next(0, 5));
        }
    } else {
        n = rnd.next(5, 100);
        s = randomString(n);
    }

    println(n);
    println(s);
    return 0;
}
