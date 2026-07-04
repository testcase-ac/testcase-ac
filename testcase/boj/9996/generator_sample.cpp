#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomLowerString(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char('a' + rnd.next(26)));
    }
    return s;
}

string mutateChar(char c) {
    return string(1, char('a' + ((c - 'a' + rnd.next(1, 25)) % 26)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int prefixLen = rnd.next(1, 8);
    int suffixLen = rnd.next(1, 8);
    string prefix = randomLowerString(prefixLen, prefixLen);
    string suffix = randomLowerString(suffixLen, suffixLen);
    string pattern = prefix + "*" + suffix;

    int n = rnd.next(8, 24);
    vector<string> names;
    names.reserve(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 7);
        string name;

        if (mode <= 2) {
            name = prefix + randomLowerString(0, 12) + suffix;
        } else if (mode == 3) {
            name = prefix + suffix;
        } else if (mode == 4) {
            name = randomLowerString(1, 8) + suffix;
            if (name.rfind(prefix, 0) == 0) {
                name[0] = mutateChar(name[0])[0];
            }
        } else if (mode == 5) {
            name = prefix + randomLowerString(1, 8);
            if (name.size() >= suffix.size() &&
                name.compare(name.size() - suffix.size(), suffix.size(), suffix) == 0) {
                name.back() = mutateChar(name.back())[0];
            }
        } else if (mode == 6) {
            int maxLen = max(1, prefixLen + suffixLen - 1);
            name = randomLowerString(1, maxLen);
        } else {
            string middle = randomLowerString(0, 8);
            name = prefix + middle + suffix;
            if (rnd.next(2) == 0) {
                name[0] = mutateChar(name[0])[0];
            } else {
                name.back() = mutateChar(name.back())[0];
            }
        }

        if ((int)name.size() > 100) {
            name.resize(100);
        }
        if (name.empty()) {
            name = "a";
        }
        names.push_back(name);
    }

    println(n);
    println(pattern);
    for (const string& name : names) {
        println(name);
    }

    return 0;
}
