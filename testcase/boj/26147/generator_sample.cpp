#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string randomPattern(int yWeight, int gWeight) {
    string s;
    for (int i = 0; i < 5; ++i) {
        int pick = rnd.next(1, yWeight + gWeight + 10);
        if (pick <= yWeight) {
            s += 'Y';
        } else if (pick <= yWeight + gWeight) {
            s += 'G';
        } else {
            s += 'B';
        }
    }
    return s;
}

string withCounts(int greenCount, int yellowCount) {
    vector<char> cells(5, 'B');
    vector<int> pos = {0, 1, 2, 3, 4};
    shuffle(pos.begin(), pos.end());
    for (int i = 0; i < greenCount; ++i) {
        cells[pos[i]] = 'G';
    }
    for (int i = 0; i < yellowCount; ++i) {
        cells[pos[greenCount + i]] = 'Y';
    }
    return string(cells.begin(), cells.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<string> patterns;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            patterns.push_back(randomPattern(rnd.next(1, 8), rnd.next(1, 8)));
        }
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        for (int i = 0; i < n; ++i) {
            int greenCount = rnd.next(0, 5);
            int yellowCount = rnd.next(0, 5 - greenCount);
            patterns.push_back(withCounts(greenCount, yellowCount));
        }
    } else if (mode == 2) {
        patterns = {"YYYYY", "GYYYY", "GGYYY", "GGGYY", "GGGGY", "GGGGG"};
        shuffle(patterns.begin(), patterns.end());
        n = rnd.next(1, (int)patterns.size());
        patterns.resize(n);
    } else if (mode == 3) {
        n = rnd.next(5, 14);
        for (int i = 0; i < n; ++i) {
            int yellowCount = rnd.next(0, 5);
            patterns.push_back(withCounts(0, yellowCount));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 14);
        for (int i = 0; i < n; ++i) {
            int greenCount = rnd.next(0, 5);
            patterns.push_back(withCounts(greenCount, 0));
        }
    } else {
        n = rnd.next(6, 16);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                patterns.push_back(withCounts(4, 1));
            } else {
                patterns.push_back(randomPattern(5, 5));
            }
        }
    }

    println((int)patterns.size());
    for (const string& pattern : patterns) {
        println(pattern);
    }

    return 0;
}
