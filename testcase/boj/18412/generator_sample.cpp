#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string buildString(int n, int pattern) {
    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lower = "abcdefghijklmnopqrstuvwxyz";
    const string mixed = upper + lower;

    string s;
    s.reserve(n);
    if (pattern == 0) {
        char c = rnd.any(mixed);
        s.assign(n, c);
    } else if (pattern == 1) {
        for (int i = 0; i < n; ++i) s.push_back((i % 2 == 0) ? 'a' : 'Z');
    } else if (pattern == 2) {
        int alphabetSize = rnd.next(2, min(8, static_cast<int>(mixed.size())));
        for (int i = 0; i < n; ++i) s.push_back(mixed[rnd.next(alphabetSize)]);
    } else if (pattern == 3) {
        for (int i = 0; i < n; ++i) s.push_back(rnd.any(lower));
    } else if (pattern == 4) {
        for (int i = 0; i < n; ++i) s.push_back(rnd.any(upper));
    } else {
        for (int i = 0; i < n; ++i) s.push_back(rnd.any(mixed));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(2, 200);
    }

    int a = 1;
    int b = n;
    if (mode == 0) {
        a = b = 1;
    } else if (mode == 1) {
        a = b = rnd.next(1, n);
    } else if (mode == 2) {
        a = 1;
        b = rnd.next(1, n);
    } else if (mode == 3) {
        a = rnd.next(1, n);
        b = n;
    } else if (mode == 4) {
        a = rnd.next(1, n);
        b = rnd.next(a, n);
    }

    int pattern = rnd.next(6);
    string s = buildString(n, pattern);

    println(n, a, b);
    println(s);
    return 0;
}
