#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomDifferentNonNeighbor(char prev) {
    vector<char> candidates;
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (abs(c - prev) != 1) candidates.push_back(c);
    }
    return rnd.any(candidates);
}

char randomNeighbor(char c) {
    if (c == 'A') return 'B';
    if (c == 'Z') return 'Y';
    return rnd.next(0, 1) == 0 ? char(c - 1) : char(c + 1);
}

string randomWalk(int len) {
    string s;
    char cur = char('A' + rnd.next(26));
    s.push_back(cur);
    for (int i = 1; i < len; ++i) {
        cur = randomNeighbor(cur);
        s.push_back(cur);
    }
    return s;
}

string losingString(int n) {
    string s;
    while ((int)s.size() < n) {
        if (!s.empty()) {
            s.push_back(randomDifferentNonNeighbor(s.back()));
            if ((int)s.size() == n) break;
        }

        int remaining = n - (int)s.size();
        int walkLen = min(remaining, rnd.next(1, 4));
        string walk = randomWalk(walkLen);
        if (!s.empty() && abs(walk.front() - s.back()) == 1) {
            walk.front() = randomDifferentNonNeighbor(s.back());
        }
        s += walk;
    }
    return s;
}

string winningString(int n) {
    string s = losingString(n);
    int len = rnd.next(5, min(n, 12));
    string win = randomWalk(len);
    int pos = rnd.next(0, n - len);
    for (int i = 0; i < len; ++i) {
        s[pos + i] = win[i];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 5;
    } else if (mode == 1) {
        n = rnd.next(6, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 30);
    } else if (mode == 3) {
        n = rnd.next(31, 80);
    } else {
        n = rnd.next(5, 30);
    }

    string s;
    if (mode == 4) {
        s.assign(n, char('A' + rnd.next(26)));
    } else if (mode == 5 || rnd.next(0, 1) == 1) {
        s = winningString(n);
    } else {
        s = losingString(n);
    }

    println(n);
    println(s);

    return 0;
}
