#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomWord(int len, bool mixedCase) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        char c = static_cast<char>('a' + rnd.next(0, 25));
        if (mixedCase && rnd.next(0, 2) == 0) {
            c = static_cast<char>('A' + (c - 'a'));
        }
        s.push_back(c);
    }
    return s;
}

string randomTrackName(int mode) {
    static const vector<string> baseNames = {
        "Alpha",       "alpha",        "ALPHA",       "Alpine",
        "Beta",        "beta",         "Beat-99",     "Blue Moon",
        "Echo",        "echo",         "Encore!",     "Forever",
        "No Air",      "No-air",       "Prelude 02",  "Prelude 10",
        "Take A Bow",  "take a bow",   "Zeta",        "zeta",
    };

    string name;
    if (mode == 0) {
        name = rnd.any(baseNames);
    } else if (mode == 1) {
        char first = static_cast<char>((rnd.next(0, 1) ? 'A' : 'a') + rnd.next(0, 25));
        name = first + string(" ") + randomWord(rnd.next(1, 8), true);
        if (rnd.next(0, 2) == 0) name += " " + to_string(rnd.next(0, 99));
    } else if (mode == 2) {
        name = randomWord(rnd.next(1, 18), true);
        if (rnd.next(0, 2) == 0) name += rnd.any(vector<string>{"!", "'", "-", "?"});
    } else if (mode == 3) {
        name = rnd.any(vector<string>{"Same", "same", "SAME", "SaMe"});
        name += rnd.any(vector<string>{"", " ", "  ", " - live", " 01"});
    } else {
        int len = rnd.next(25, 80);
        name = randomWord(len, true);
    }

    if (rnd.next(0, 5) == 0 && (int)name.size() < 248) {
        name += string(rnd.next(1, min(3, 250 - (int)name.size())), ' ');
    }

    return name;
}

vector<string> makeScenario(int mode) {
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 4) {
        n = rnd.next(15, 35);
    } else {
        n = rnd.next(3, 12);
    }

    vector<string> names;
    names.reserve(n);
    for (int i = 0; i < n; ++i) {
        names.push_back(randomTrackName(mode));
    }

    if (mode == 1) {
        sort(names.begin(), names.end());
    } else if (mode == 2) {
        sort(names.begin(), names.end());
        reverse(names.begin(), names.end());
    } else {
        shuffle(names.begin(), names.end());
    }

    return names;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenarios = rnd.next(1, 5);
    for (int scenario = 0; scenario < scenarios; ++scenario) {
        int mode = scenario < 5 ? scenario : rnd.next(0, 4);
        vector<string> names = makeScenario(mode);

        println(static_cast<int>(names.size()));
        for (const string& name : names) {
            println(name);
        }
    }
    println(0);

    return 0;
}
