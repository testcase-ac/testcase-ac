#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomSide(int length, int bias) {
    string side;
    side.reserve(length);
    for (int i = 0; i < length; ++i) {
        if (bias == 0) {
            side.push_back(rnd.next(0, 3) == 0 ? 'B' : 'A');
        } else if (bias == 1) {
            side.push_back(rnd.next(0, 3) == 0 ? 'A' : 'B');
        } else if (bias == 2) {
            side.push_back(i % 2 == 0 ? 'A' : 'B');
        } else if (bias == 3) {
            side.push_back(i % 2 == 0 ? 'B' : 'A');
        } else {
            side.push_back(rnd.next(0, 1) == 0 ? 'A' : 'B');
        }
    }
    return side;
}

string makeCase(int mode) {
    string left;
    string right;

    if (mode == 0) {
        left = randomSide(rnd.next(0, 4), rnd.next(0, 4));
        right = randomSide(rnd.next(1, 8), rnd.next(0, 4));
    } else if (mode == 1) {
        left = randomSide(rnd.next(1, 8), rnd.next(0, 4));
        right = randomSide(rnd.next(0, 4), rnd.next(0, 4));
    } else if (mode == 2) {
        int aBlock = rnd.next(1, 6);
        int bBlock = rnd.next(1, 6);
        left = string(aBlock, 'A') + string(bBlock, 'B');
        right = string(rnd.next(1, 6), rnd.next(0, 1) == 0 ? 'A' : 'B');
    } else if (mode == 3) {
        int bBlock = rnd.next(1, 6);
        int aBlock = rnd.next(1, 6);
        left = string(rnd.next(1, 6), rnd.next(0, 1) == 0 ? 'A' : 'B');
        right = string(bBlock, 'B') + string(aBlock, 'A');
    } else if (mode == 4) {
        int length = rnd.next(2, 14);
        left = randomSide(length, rnd.next(2, 3));
        right = left;
        if (rnd.next(0, 1) == 0) {
            reverse(right.begin(), right.end());
        }
    } else {
        int totalLength = rnd.next(3, 40);
        int coconut = rnd.next(0, totalLength - 1);
        left = randomSide(coconut, rnd.next(0, 4));
        right = randomSide(totalLength - coconut - 1, rnd.next(0, 4));
    }

    string s = left + "C" + right;
    while (s.size() < 3) {
        if (rnd.next(0, 1) == 0) {
            s.insert(s.begin(), rnd.next(0, 1) == 0 ? 'A' : 'B');
        } else {
            s.push_back(rnd.next(0, 1) == 0 ? 'A' : 'B');
        }
    }
    if (s.find('A') == string::npos) {
        vector<int> positions;
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            if (s[i] != 'C') {
                positions.push_back(i);
            }
        }
        int pos = rnd.any(positions);
        s[pos] = 'A';
    }
    if (s.find('B') == string::npos) {
        vector<int> positions;
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            if (s[i] != 'C') {
                positions.push_back(i);
            }
        }
        int pos = rnd.any(positions);
        s[pos] = 'B';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 30);
    vector<string> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}
