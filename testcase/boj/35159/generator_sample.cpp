#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static string shuffledWithCounts(int kCount, int cCount, int pCount) {
    string s;
    s.append(kCount, 'K');
    s.append(cCount, 'C');
    s.append(pCount, 'P');
    shuffle(s.begin(), s.end());
    return s;
}

static string runString(const vector<pair<char, int>>& runs) {
    string s;
    for (auto [ch, len] : runs) {
        s.append(len, ch);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int repeat = rnd.next(1, 8);
        s = "KCPC";
        for (int i = 0; i < repeat; ++i) {
            s += rnd.any(string("KCP"));
        }
        shuffle(s.begin(), s.end());
    } else if (mode == 1) {
        int kCount = rnd.next(1, 8);
        int cCount = rnd.next(2, 16);
        int pCount = rnd.next(1, 8);
        s = shuffledWithCounts(kCount, cCount, pCount);
    } else if (mode == 2) {
        vector<pair<char, int>> runs = {
            {'K', rnd.next(1, 5)},
            {'C', rnd.next(1, 7)},
            {'P', rnd.next(1, 5)},
            {'C', rnd.next(1, 7)},
        };
        if (rnd.next(2)) {
            runs.insert(runs.begin(), {rnd.any(string("CP")), rnd.next(1, 4)});
        }
        if (rnd.next(2)) {
            runs.push_back({rnd.any(string("KP")), rnd.next(1, 4)});
        }
        s = runString(runs);
    } else if (mode == 3) {
        int middle = rnd.next(0, 10);
        s = runString({
            {'C', rnd.next(1, 8)},
            {'K', rnd.next(1, 5)},
            {'C', rnd.next(1, 8)},
            {'P', rnd.next(1, 5)},
            {'C', rnd.next(1, 8)},
        });
        for (int i = 0; i < middle; ++i) {
            int pos = rnd.next(0, int(s.size()));
            s.insert(s.begin() + pos, rnd.any(string("KCP")));
        }
    } else if (mode == 4) {
        int kCount = rnd.next(1, 3);
        int cCount = rnd.next(2, 6);
        int pCount = rnd.next(1, 3);
        s = shuffledWithCounts(kCount, cCount, pCount);
    } else {
        int len = rnd.next(20, 80);
        s = "KCCP";
        while ((int)s.size() < len) {
            char ch = rnd.any(string("KCP"));
            int run = rnd.next(1, min(8, len - int(s.size())));
            s.append(run, ch);
        }
        shuffle(s.begin(), s.end());
    }

    println(s);
    return 0;
}
