#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('a' + rnd.next(0, alphabetSize - 1)));
    }
    return s;
}

string blockReversalResult(const string& s, int cutPercent) {
    vector<string> blocks;
    int start = 0;
    for (int i = 1; i <= (int)s.size(); ++i) {
        if (i == (int)s.size() || rnd.next(0, 99) < cutPercent) {
            blocks.push_back(s.substr(start, i - start));
            start = i;
        }
    }

    string t;
    t.reserve(s.size());
    for (int i = (int)blocks.size() - 1; i >= 0; --i) {
        t += blocks[i];
    }
    return t;
}

string shuffledAnagramDifferentFrom(const string& s, const string& avoid) {
    string t = s;
    for (int attempt = 0; attempt < 30; ++attempt) {
        shuffle(t.begin(), t.end());
        if (t != avoid) {
            return t;
        }
    }

    if ((int)t.size() >= 2) {
        swap(t[0], t[1]);
    }
    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(2, 18);
    }

    int alphabetSize;
    if (mode == 4) {
        alphabetSize = rnd.next(1, 3);
    } else {
        alphabetSize = rnd.next(2, 6);
    }

    string s = randomString(n, alphabetSize);
    string t;

    if (mode == 0 || mode == 1) {
        t = s;
    } else if (mode == 2) {
        t = blockReversalResult(s, rnd.next(15, 45));
    } else if (mode == 3) {
        t = blockReversalResult(s, rnd.next(65, 95));
    } else if (mode == 4) {
        string valid = blockReversalResult(s, rnd.next(25, 80));
        t = shuffledAnagramDifferentFrom(s, valid);
    } else {
        t = randomString(n, alphabetSize);
    }

    println(n);
    println(s);
    println(t);
    return 0;
}
