#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string shuffledSequence(int r) {
    string s(r + 4, 'L');
    s += string(r, 'R');
    shuffle(s.begin(), s.end());
    return s;
}

string alternatingSequence(int r) {
    string s;
    int left = r + 4;
    int right = r;
    bool startWithRight = rnd.next(0, 1);
    while (left > 0 || right > 0) {
        if (startWithRight && right > 0) {
            s.push_back('R');
            --right;
        }
        if (left > 0) {
            s.push_back('L');
            --left;
        }
        startWithRight = !startWithRight;
    }
    return s;
}

string clusteredSequence(int r) {
    int left = r + 4;
    int right = r;
    string s;
    bool takeLeft = rnd.next(0, 1);
    while (left > 0 || right > 0) {
        if ((takeLeft && left > 0) || right == 0) {
            int run = rnd.next(1, min(left, 5));
            s += string(run, 'L');
            left -= run;
        } else {
            int run = rnd.next(1, min(right, 4));
            s += string(run, 'R');
            right -= run;
        }
        takeLeft = !takeLeft;
    }

    int rotateBy = rnd.next(0, int(s.size()) - 1);
    rotate(s.begin(), s.begin() + rotateBy, s.end());
    return s;
}

string burstSequence(int r) {
    int prefixLeft = rnd.next(0, r + 4);
    int suffixLeft = r + 4 - prefixLeft;
    return string(prefixLeft, 'L') + string(r, 'R') + string(suffixLeft, 'L');
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    vector<string> cases;
    cases.reserve(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int r;
        if (tc == 0 && rnd.next(0, 3) == 0) {
            r = 0;
        } else if (mode == 5) {
            r = rnd.next(20, 60);
        } else {
            r = rnd.next(0, 18);
        }

        string s;
        if (mode == 0) {
            s = shuffledSequence(r);
        } else if (mode == 1) {
            s = alternatingSequence(r);
        } else if (mode == 2) {
            s = clusteredSequence(r);
        } else if (mode == 3) {
            s = burstSequence(r);
        } else if (mode == 4) {
            s = string(r + 4, 'L') + string(r, 'R');
        } else {
            s = string(r, 'R') + string(r + 4, 'L');
        }

        cases.push_back(s);
    }

    println(t);
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
