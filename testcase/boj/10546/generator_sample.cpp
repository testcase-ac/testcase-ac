#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

string makeName(int index, int maxLen) {
    string name;
    ++index;
    while (index > 0) {
        name.push_back(char('a' + (index - 1) % 26));
        index = (index - 1) / 26;
    }
    while ((int)name.size() < maxLen && rnd.next(4) == 0) {
        name.push_back(char('a' + rnd.next(26)));
    }
    return name;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(2, 15);
    } else if (mode == 2) {
        n = rnd.next(8, 30);
    } else {
        n = rnd.next(20, 45);
    }

    int uniqueCount = 1;
    if (mode == 0) {
        uniqueCount = rnd.next(1, n);
    } else if (mode == 1) {
        uniqueCount = rnd.next(1, min(n, 4));
    } else if (mode == 2) {
        uniqueCount = rnd.next(max(1, n / 2), n);
    } else {
        uniqueCount = rnd.next(1, min(n, 8));
    }

    int maxExtraLen = rnd.next(1, 20);
    vector<string> pool;
    for (int i = 0; i < uniqueCount; ++i) {
        pool.push_back(makeName(i, maxExtraLen));
    }

    vector<string> registered;
    if (mode == 1 || mode == 3) {
        string repeated = rnd.any(pool);
        int repeatedCount = rnd.next(1, n);
        for (int i = 0; i < repeatedCount; ++i) {
            registered.push_back(repeated);
        }
    }
    while ((int)registered.size() < n) {
        registered.push_back(rnd.any(pool));
    }
    shuffle(registered.begin(), registered.end());

    int missingIndex = rnd.next(n);
    vector<string> finishers;
    for (int i = 0; i < n; ++i) {
        if (i != missingIndex) {
            finishers.push_back(registered[i]);
        }
    }
    shuffle(finishers.begin(), finishers.end());

    println(n);
    for (const string& name : registered) {
        println(name);
    }
    for (const string& name : finishers) {
        println(name);
    }

    return 0;
}
