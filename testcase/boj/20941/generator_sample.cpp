#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string alternatingString(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back((i % 2 == 0) ? first : char('0' + '1' - first));
    }
    return s;
}

string blockString(int n) {
    string s(n, '0');
    int split = rnd.next(0, n);
    for (int i = split; i < n; ++i) s[i] = '1';
    if (rnd.next(0, 1)) {
        for (char& c : s) c = (c == '0' ? '1' : '0');
    }
    return s;
}

string sparseString(int n, int ones) {
    string s(n, '0');
    vector<int> positions(n);
    for (int i = 0; i < n; ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    for (int i = 0; i < ones; ++i) s[positions[i]] = '1';
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 20);

    if (mode == 0) {
        n = rnd.any(vector<int>{1, 2, 3});
    } else if (mode == 1) {
        n = rnd.next(16, 20);
    }

    string p;
    if (mode == 0) {
        p = string(n, rnd.next(0, 1) ? '1' : '0');
    } else if (mode == 1) {
        p = alternatingString(n, rnd.next(0, 1) ? '1' : '0');
    } else if (mode == 2) {
        p = blockString(n);
    } else if (mode == 3) {
        p = sparseString(n, rnd.next(0, min(n, 3)));
    } else if (mode == 4) {
        p = sparseString(n, n - rnd.next(0, min(n, 3)));
    } else {
        p.resize(n);
        for (char& c : p) c = rnd.next(0, 1) ? '1' : '0';
    }

    println(n);
    println(p);

    return 0;
}
