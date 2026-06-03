#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string randomName(int len, char lo = 'A', char hi = 'Z') {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char(rnd.next(int(lo), int(hi)));
    }
    return s;
}

void addUnique(vector<string>& names, set<string>& used, const string& name) {
    if (used.insert(name).second) {
        names.push_back(name);
    }
}

void addRandomUnique(vector<string>& names, set<string>& used, int len, char lo = 'A', char hi = 'Z') {
    while (true) {
        string name = randomName(len, lo, hi);
        if (used.insert(name).second) {
            names.push_back(name);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 25);

    vector<string> names;
    set<string> used;

    if (mode == 0) {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            addRandomUnique(names, used, 3);
        }
    } else if (mode == 1) {
        n = rnd.next(5, 25);
        addRandomUnique(names, used, 3, 'A', 'D');
        for (int i = 1; i < n; ++i) {
            int len = rnd.next(2, 5);
            addRandomUnique(names, used, len, 'A', 'F');
        }
    } else if (mode == 2) {
        vector<string> candidates = {
            "AA", "AAA", "AAAA", "AAAAA", "AAB", "AAC", "ABA", "ABAA",
            "BA", "BAA", "BAC", "BACA", "CAB", "CABA", "ZZ", "ZZZ"
        };
        shuffle(candidates.begin(), candidates.end());
        n = rnd.next(3, int(candidates.size()));
        for (int i = 0; i < n; ++i) {
            addUnique(names, used, candidates[i]);
        }
        if (!used.count("AAA") && !used.count("AAB") && !used.count("AAC") &&
            !used.count("ABA") && !used.count("BAA") && !used.count("BAC") &&
            !used.count("CAB") && !used.count("ZZZ")) {
            addUnique(names, used, "AAA");
        }
    } else {
        vector<string> anchors = {"AAA", "AAB", "ABC", "AZZ", "BAA", "ZZZ"};
        addUnique(names, used, rnd.any(anchors));
        while (int(names.size()) < n) {
            int len = rnd.next(2, 5);
            char hi = rnd.next(0, 1) == 0 ? 'C' : 'Z';
            addRandomUnique(names, used, len, 'A', hi);
        }
    }

    shuffle(names.begin(), names.end());

    println(int(names.size()));
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
