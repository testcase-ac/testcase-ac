#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomName(int l) {
    string s;
    for (int i = 0; i < l; ++i) s += char('A' + rnd.next(26));
    return s;
}

char differentChar(char c) {
    char next = char('A' + rnd.next(25));
    if (next >= c) ++next;
    return next;
}

void addUnique(vector<string>& names, set<string>& used, const string& name) {
    if (used.insert(name).second) names.push_back(name);
}

vector<string> makeNearCluster(int n, int l) {
    string base = randomName(l);
    vector<string> names;
    set<string> used;

    addUnique(names, used, base);
    while ((int)names.size() < n) {
        string candidate = base;
        int pos = rnd.next(l);
        candidate[pos] = differentChar(candidate[pos]);
        addUnique(names, used, candidate);
    }

    shuffle(names.begin(), names.end());
    return names;
}

vector<string> makeNoAnswerCluster(int n, int l) {
    vector<string> names;
    set<string> used;

    string suffix;
    for (int i = 2; i < l; ++i) suffix += char('A' + rnd.next(3));

    addUnique(names, used, "AA" + suffix);
    addUnique(names, used, "BB" + suffix);
    addUnique(names, used, "CC" + suffix);

    while ((int)names.size() < n) {
        string candidate = randomName(l);
        addUnique(names, used, candidate);
    }

    shuffle(names.begin(), names.end());
    return names;
}

vector<string> makeRandomSet(int n, int l) {
    vector<string> names;
    set<string> used;

    while ((int)names.size() < n) {
        addUnique(names, used, randomName(l));
    }

    return names;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int l = rnd.next(1, 12);
    int n = rnd.next(1, min(12, 26 * l));
    vector<string> names;

    if (mode <= 1) {
        names = makeNearCluster(n, l);
    } else if (mode == 2 && l >= 2) {
        n = max(n, 3);
        names = makeNoAnswerCluster(n, l);
    } else if (mode == 3) {
        l = rnd.next(13, 20);
        n = rnd.next(2, 8);
        names = makeNearCluster(n, l);
    } else {
        names = makeRandomSet(n, l);
    }

    println((int)names.size(), l);
    for (const string& name : names) println(name);

    return 0;
}
