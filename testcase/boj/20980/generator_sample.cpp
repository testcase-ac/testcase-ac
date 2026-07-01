#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeGoodTower(int n) {
    int a = rnd.next(0, n);
    int b = rnd.next(0, n - a);
    int c = n - a - b;
    return string(a, 'A') + string(b, 'B') + string(c, 'C');
}

string randomTower(int n) {
    string s;
    string alphabet = "ABC";
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string biasedTower(int n) {
    string s;
    char common = rnd.any(string("ABC"));
    for (int i = 0; i < n; ++i) {
        if (rnd.next(100) < 70) {
            s += common;
        } else {
            s += rnd.any(string("ABC"));
        }
    }
    return s;
}

string alternatingTower(int n) {
    string letters = "ABC";
    shuffle(letters.begin(), letters.end());

    string s;
    for (int i = 0; i < n; ++i) {
        s += letters[i % (rnd.next(2, 3))];
    }
    return s;
}

string shuffledBlocksTower(int n) {
    string s = makeGoodTower(n);
    vector<pair<int, int>> blocks;
    int start = 0;
    while (start < n) {
        int len = rnd.next(1, min(4, n - start));
        blocks.push_back({start, len});
        start += len;
    }
    shuffle(blocks.begin(), blocks.end());

    string t;
    for (auto block : blocks) {
        t += s.substr(block.first, block.second);
    }
    return t;
}

string prefixFlippedTower(int n) {
    string s = makeGoodTower(n);
    int flips = rnd.next(1, min(5, n));
    for (int i = 0; i < flips; ++i) {
        int k = rnd.next(2, n);
        reverse(s.begin(), s.begin() + k);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> interestingN = {2, 3, 4, 5, 8, 13};
    int n = rnd.next(100) < 45 ? rnd.any(interestingN) : rnd.next(2, 13);
    int q = rnd.next(1, 30);

    println(n, q);
    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 6);
        string s;
        if (mode == 0) {
            s = makeGoodTower(n);
        } else if (mode == 1) {
            s = makeGoodTower(n);
            reverse(s.begin(), s.end());
        } else if (mode == 2) {
            s = randomTower(n);
        } else if (mode == 3) {
            s = biasedTower(n);
        } else if (mode == 4) {
            s = alternatingTower(n);
        } else if (mode == 5) {
            s = shuffledBlocksTower(n);
        } else {
            s = prefixFlippedTower(n);
        }
        println(s);
    }

    return 0;
}
