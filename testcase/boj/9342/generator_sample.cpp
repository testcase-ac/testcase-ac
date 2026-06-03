#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string repeatChar(char c, int count) {
    return string(count, c);
}

string infectedString() {
    string s;
    if (rnd.next(2)) {
        s += char('A' + rnd.next(6));
    }
    s += repeatChar('A', rnd.next(1, 35));
    s += repeatChar('F', rnd.next(1, 35));
    s += repeatChar('C', rnd.next(1, 35));
    if (rnd.next(2)) {
        s += char('A' + rnd.next(6));
    }
    return s;
}

string randomUppercaseString(int lo, int hi) {
    int n = rnd.next(lo, hi);
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += char('A' + rnd.next(26));
    }
    return s;
}

string nearMissString() {
    vector<string> candidates;

    candidates.push_back(repeatChar('A', rnd.next(1, 30)));
    candidates.push_back(repeatChar('F', rnd.next(1, 30)));
    candidates.push_back(repeatChar('C', rnd.next(1, 30)));
    candidates.push_back("A" + repeatChar('F', rnd.next(1, 30)));
    candidates.push_back(repeatChar('A', rnd.next(1, 30)) + repeatChar('C', rnd.next(1, 30)));
    candidates.push_back(repeatChar('F', rnd.next(1, 30)) + repeatChar('C', rnd.next(1, 30)));

    string base = infectedString();
    int mode = rnd.next(4);
    if (mode == 0) {
        char bad = char('G' + rnd.next(20));
        int pos = rnd.next((int)base.size() + 1);
        base.insert(base.begin() + pos, bad);
    } else if (mode == 1) {
        base += randomUppercaseString(1, 8);
    } else if (mode == 2 && base.size() > 1) {
        int pos = rnd.next((int)base.size());
        base[pos] = char('G' + rnd.next(20));
    } else {
        shuffle(base.begin(), base.end());
    }
    candidates.push_back(base);

    string chosen = rnd.any(candidates);
    if ((int)chosen.size() > 200) {
        chosen.resize(200);
    }
    return chosen;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(100);
        string s;
        if (mode < 35) {
            s = infectedString();
        } else if (mode < 75) {
            s = nearMissString();
        } else if (mode < 90) {
            s = randomUppercaseString(1, 25);
        } else {
            s = randomUppercaseString(120, 200);
        }
        println(s);
    }

    return 0;
}
