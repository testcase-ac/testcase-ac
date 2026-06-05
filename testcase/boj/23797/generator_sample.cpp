#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeAlternating(int n, char first) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        bool sameParity = (i % 2 == 0);
        s.push_back(sameParity ? first : (first == 'K' ? 'P' : 'K'));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 45);
    string s;

    if (mode == 0) {
        s = string(n, rnd.next(0, 1) == 0 ? 'K' : 'P');
    } else if (mode == 1) {
        s = makeAlternating(n, rnd.next(0, 1) == 0 ? 'K' : 'P');
    } else if (mode == 2) {
        int blockCount = rnd.next(2, 12);
        char cur = rnd.next(0, 1) == 0 ? 'K' : 'P';
        for (int i = 0; i < blockCount; ++i) {
            int len = rnd.next(1, 8);
            s += string(len, cur);
            if (rnd.next(0, 99) < 75) cur = (cur == 'K' ? 'P' : 'K');
        }
    } else if (mode == 3) {
        int frogs = rnd.next(2, 12);
        vector<string> voices;
        for (int i = 0; i < frogs; ++i) {
            int len = rnd.next(1, 8);
            voices.push_back(makeAlternating(len, rnd.next(0, 1) == 0 ? 'K' : 'P'));
        }
        vector<int> pos(frogs, 0);
        while (true) {
            vector<int> alive;
            for (int i = 0; i < frogs; ++i) {
                if (pos[i] < int(voices[i].size())) alive.push_back(i);
            }
            if (alive.empty()) break;
            int who = rnd.any(alive);
            s.push_back(voices[who][pos[who]++]);
        }
    } else if (mode == 4) {
        double kProb = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next() < kProb ? 'K' : 'P');
        }
    } else {
        int prefix = rnd.next(1, 12);
        int middle = rnd.next(0, 20);
        int suffix = rnd.next(1, 12);
        char edge = rnd.next(0, 1) == 0 ? 'K' : 'P';
        s = string(prefix, edge);
        s += makeAlternating(middle, edge == 'K' ? 'P' : 'K');
        s += string(suffix, edge);
    }

    println(s);
    return 0;
}
