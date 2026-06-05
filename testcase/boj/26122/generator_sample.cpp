#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string alternating(int k) {
    string s;
    s.reserve(k);
    char first = rnd.next(0, 1) ? 'N' : 'S';
    for (int i = 0; i < k; ++i) {
        s.push_back((i % 2 == 0) ? first : (first == 'N' ? 'S' : 'N'));
    }
    return s;
}

string randomRuns(int k) {
    string s;
    s.reserve(k);
    char c = rnd.next(0, 1) ? 'N' : 'S';
    while ((int)s.size() < k) {
        int remaining = k - (int)s.size();
        int run = rnd.next(1, min(remaining, rnd.next(1, 12)));
        s.append(run, c);
        c = (c == 'N' ? 'S' : 'N');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = rnd.next(1, 80);
    string s;

    if (mode == 0) {
        s.assign(k, rnd.next(0, 1) ? 'N' : 'S');
    } else if (mode == 1) {
        s = alternating(k);
    } else if (mode == 2) {
        int left = rnd.next(1, k);
        char c = rnd.next(0, 1) ? 'N' : 'S';
        s.assign(left, c);
        s.append(k - left, c == 'N' ? 'S' : 'N');
    } else if (mode == 3) {
        int run = rnd.next(1, 30);
        char c = rnd.next(0, 1) ? 'N' : 'S';
        s.assign(run, c);
        s.append(run, c == 'N' ? 'S' : 'N');
        if (rnd.next(0, 1)) {
            int pad = rnd.next(0, 20);
            s.insert(0, pad, rnd.next(0, 1) ? 'N' : 'S');
        }
        if (rnd.next(0, 1)) {
            int pad = rnd.next(0, 20);
            s.append(pad, rnd.next(0, 1) ? 'N' : 'S');
        }
        k = (int)s.size();
    } else if (mode == 4) {
        s = randomRuns(k);
    } else {
        k = rnd.next(40, 180);
        s = randomRuns(k);
    }

    println(k);
    println(s);
    return 0;
}
