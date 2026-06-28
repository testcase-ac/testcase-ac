#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static char opposite(char c) {
    if (c == 'L') return 'R';
    if (c == 'R') return 'L';
    if (c == 'D') return 'U';
    return 'D';
}

static string randomWalk(int n) {
    const string dirs = "LRDU";
    string s;
    s.reserve(n);

    char last = dirs[rnd.next(4)];
    for (int i = 0; i < n; ++i) {
        int choice = rnd.next(100);
        if (i > 0 && choice < 30) {
            last = opposite(last);
        } else if (i > 0 && choice < 55) {
            // Keep moving in the same direction to create longer translated suffixes.
        } else {
            last = dirs[rnd.next(4)];
        }
        s.push_back(last);
    }

    return s;
}

static string loopBlocks(int n) {
    vector<string> blocks = {"LR", "RL", "UD", "DU", "LURD", "RDLU", "LLRR", "UUDD"};
    string s;
    s.reserve(n);

    while ((int)s.size() < n) {
        string block = blocks[rnd.next((int)blocks.size())];
        if (rnd.next(2)) {
            for (char& c : block) c = opposite(c);
        }
        for (char c : block) {
            if ((int)s.size() == n) break;
            s.push_back(c);
        }
    }

    return s;
}

static string biasedAxis(int n) {
    char primary = rnd.next(2) ? 'L' : 'R';
    char secondary = rnd.next(2) ? 'D' : 'U';
    string s;
    s.reserve(n);

    for (int i = 0; i < n; ++i) {
        int choice = rnd.next(100);
        if (choice < 55) {
            s.push_back(primary);
        } else if (choice < 75) {
            s.push_back(opposite(primary));
        } else if (choice < 90) {
            s.push_back(secondary);
        } else {
            s.push_back(opposite(secondary));
        }
    }

    return s;
}

static string repeatedPattern(int n) {
    const string dirs = "LRDU";
    int patternLength = rnd.next(2, 8);
    string pattern;
    pattern.reserve(patternLength);
    for (int i = 0; i < patternLength; ++i) {
        pattern.push_back(dirs[rnd.next(4)]);
    }

    string s;
    s.reserve(n);
    while ((int)s.size() < n) {
        for (char c : pattern) {
            if ((int)s.size() == n) break;
            s.push_back(c);
        }
        if (rnd.next(100) < 20) {
            pattern[rnd.next(patternLength)] = dirs[rnd.next(4)];
        }
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 80) {
        n = rnd.next(2, 80);
    } else {
        n = rnd.next(81, 300);
    }

    int mode = rnd.next(4);
    string commands;
    if (mode == 0) {
        commands = randomWalk(n);
    } else if (mode == 1) {
        commands = loopBlocks(n);
    } else if (mode == 2) {
        commands = biasedAxis(n);
    } else {
        commands = repeatedPattern(n);
    }

    println(n);
    println(commands);

    return 0;
}
