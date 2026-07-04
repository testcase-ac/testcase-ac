#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string alternatingString(int len) {
    string s;
    s.reserve(len);
    char first = rnd.next(0, 1) ? 'D' : 'G';
    for (int i = 0; i < len; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == 'D' ? 'G' : 'D'));
    }
    return s;
}

string biasedString(int len) {
    string s;
    s.reserve(len);
    int duckPercent = rnd.next(10, 90);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.next(1, 100) <= duckPercent ? 'D' : 'G');
    }
    return s;
}

string runString(int len) {
    string s;
    char bird = rnd.next(0, 1) ? 'D' : 'G';
    while ((int)s.size() < len) {
        int remaining = len - (int)s.size();
        int block = min(remaining, rnd.next(1, min(8, remaining)));
        s.append(block, bird);
        bird = (bird == 'D' ? 'G' : 'D');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int len;
    int n;
    int k;
    string s;

    if (mode == 0) {
        len = rnd.next(1, 8);
        n = rnd.next(1, 5);
        k = rnd.next(1, 5);
        s = biasedString(len);
    } else if (mode == 1) {
        len = rnd.next(10, 40);
        n = rnd.next(1, min(10, len));
        k = rnd.next(1, 10);
        s = alternatingString(len);
    } else if (mode == 2) {
        len = rnd.next(8, 60);
        n = rnd.next(1, min(15, len));
        k = rnd.next(1, 12);
        s = runString(len);
    } else if (mode == 3) {
        len = rnd.next(1, 30);
        n = rnd.next(len + 1, 2000);
        k = rnd.next(1, 2000);
        s = rnd.next(0, 1) ? string(len, 'D') : string(len, 'G');
    } else if (mode == 4) {
        len = rnd.next(20, 80);
        n = rnd.next(1, min(20, len));
        k = rnd.next(1, min(20, len));
        s = rnd.next(0, 1) ? string(len, 'D') : string(len, 'G');
    } else if (mode == 5) {
        len = rnd.next(20, 80);
        n = rnd.next(1, min(20, len));
        k = rnd.next(1, min(20, len));
        s = runString(len);
        int flips = rnd.next(1, max(1, len / 5));
        for (int i = 0; i < flips; ++i) {
            int pos = rnd.next(0, len - 1);
            s[pos] = (s[pos] == 'D' ? 'G' : 'D');
        }
    } else {
        len = rnd.next(50, 120);
        n = rnd.next(1, min(30, len));
        k = rnd.next(1, min(30, len));
        s = biasedString(len);
    }

    println(n, k);
    println(s);
    return 0;
}
