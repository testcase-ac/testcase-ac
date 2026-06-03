#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomName(const set<string>& used) {
    static const vector<string> pool = {
        "adam",   "alice", "alpha", "beta",  "bumin", "cake",
        "dhyang", "dongho", "eve",   "lawyer", "mango", "potato",
        "soda",   "toast", "zebra"};

    for (int tries = 0; tries < 100; ++tries) {
        string name = rnd.any(pool);
        if (name != "swi" && !used.count(name)) return name;
    }

    while (true) {
        int len = rnd.next(1, 8);
        string name;
        for (int i = 0; i < len; ++i) name += char('a' + rnd.next(26));
        if (name != "swi" && !used.count(name)) return name;
    }
}

void addUnique(vector<string>& names, set<string>& used, const string& name) {
    if (name != "swi" && !used.count(name)) {
        names.push_back(name);
        used.insert(name);
    }
}

void fillNames(vector<string>& names, set<string>& used, int target) {
    while ((int)names.size() < target) {
        addUnique(names, used, randomName(used));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> names;
    vector<string> witnesses;
    set<string> used;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        int n = rnd.next(1, 8);
        addUnique(names, used, "dongho");
        fillNames(names, used, n);
        witnesses.assign(rnd.next(0, 4), "dongho");
    } else if (mode == 1) {
        int n = rnd.next(1, 8);
        string suspect = randomName(used);
        addUnique(names, used, suspect);
        fillNames(names, used, n);
        for (const string& name : names) {
            if (name != suspect) witnesses.push_back(name);
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 8);
        vector<string> priority = {"bumin", "cake", "lawyer"};
        shuffle(priority.begin(), priority.end());
        for (const string& name : priority) addUnique(names, used, name);
        fillNames(names, used, n);
        for (const string& name : names) {
            if (name != priority[0] && rnd.next(0, 1)) witnesses.push_back(name);
        }
    } else if (mode == 3) {
        int n = rnd.next(2, 8);
        fillNames(names, used, n);
        for (const char* blocked : {"bumin", "cake", "dongho", "lawyer"}) {
            string blockedName = blocked;
            if (used.count(blockedName)) {
                names.erase(find(names.begin(), names.end(), blockedName));
                used.erase(blockedName);
                fillNames(names, used, n);
            }
        }
        sort(names.begin(), names.end());
        int firstUnseen = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i != firstUnseen && rnd.next(0, 1)) witnesses.push_back(names[i]);
        }
    } else if (mode == 4) {
        int n = rnd.next(0, 8);
        fillNames(names, used, n);
        for (const string& name : names) witnesses.push_back(name);
    } else {
        int n = rnd.next(0, 6);
        fillNames(names, used, n);
        for (int i = 0; i < rnd.next(0, 8); ++i) {
            witnesses.push_back(randomName(used));
        }
    }

    int extraWitnesses = rnd.next(0, 6);
    for (int i = 0; i < extraWitnesses; ++i) {
        if (!names.empty() && rnd.next(0, 2) == 0) {
            witnesses.push_back(rnd.any(names));
        } else {
            witnesses.push_back(randomName(used));
        }
    }
    shuffle(names.begin(), names.end());
    shuffle(witnesses.begin(), witnesses.end());

    println("swi's cake is missing!");
    println((int)names.size());
    for (const string& name : names) println(name);
    println((int)witnesses.size());
    for (const string& witness : witnesses) println(witness);

    return 0;
}
