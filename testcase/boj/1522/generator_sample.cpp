#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string alternating(int n) {
    string s;
    s.reserve(n);
    char first = rnd.next(2) == 0 ? 'a' : 'b';
    for (int i = 0; i < n; ++i) {
        s.push_back(i % 2 == 0 ? first : (first == 'a' ? 'b' : 'a'));
    }
    return s;
}

string circularBlock(int n) {
    int aCount = rnd.next(1, n);
    string s(aCount, 'a');
    s += string(n - aCount, 'b');
    int rot = rnd.next(n);
    rotate(s.begin(), s.begin() + rot, s.end());
    return s;
}

string clusteredRuns(int n) {
    string s;
    s.reserve(n);
    char cur = rnd.next(2) == 0 ? 'a' : 'b';
    while ((int)s.size() < n) {
        int remaining = n - (int)s.size();
        int run = rnd.next(1, min(remaining, rnd.next(1, 7)));
        s += string(run, cur);
        if (rnd.next(100) < 75) {
            cur = cur == 'a' ? 'b' : 'a';
        }
    }
    return s;
}

string biasedRandom(int n) {
    int aPercent = rnd.any(vector<int>{10, 25, 40, 50, 60, 75, 90});
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next(100) < aPercent ? 'a' : 'b');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 85) {
        n = rnd.next(1, 30);
    } else {
        n = rnd.next(31, 1000);
    }

    int mode = rnd.next(6);
    string s;
    if (mode == 0) {
        s = string(n, rnd.next(2) == 0 ? 'a' : 'b');
    } else if (mode == 1) {
        s = alternating(n);
    } else if (mode == 2) {
        s = circularBlock(n);
    } else if (mode == 3) {
        s = clusteredRuns(n);
    } else {
        s = biasedRandom(n);
    }

    println(s);
    return 0;
}
