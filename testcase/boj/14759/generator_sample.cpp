#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string randomName(int minLen, int maxLen, char low = 'A', char high = 'Z') {
    int len = rnd.next(minLen, maxLen);
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(char(rnd.next(int(low), int(high))));
    }
    return s;
}

string mutateLast(string s) {
    if (s.empty()) return "A";
    if (s.back() < 'Z') {
        ++s.back();
    } else {
        s.push_back(char(rnd.next(int('A'), int('Z'))));
    }
    if (int(s.size()) > 30) s.resize(30);
    return s;
}

string withSuffix(string prefix, int maxLen) {
    int extra = rnd.next(0, maxLen - int(prefix.size()));
    string s = prefix;
    for (int i = 0; i < extra; ++i) {
        s.push_back(char(rnd.next(int('A'), int('Z'))));
    }
    return s;
}

vector<string> buildCase(int mode) {
    set<string> names;
    int n = 2 * rnd.next(1, 8);

    if (mode == 0) {
        n = 2;
        string base = randomName(1, 8);
        names.insert(base);
        names.insert(mutateLast(base));
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 5);
        string prefix = randomName(1, 6, 'A', 'M');
        while (int(names.size()) < n) {
            names.insert(withSuffix(prefix, min(30, int(prefix.size()) + 8)));
        }
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 4);
        names.insert(string(rnd.next(1, 30), 'A'));
        names.insert(string(rnd.next(1, 30), 'Z'));
    } else if (mode == 3) {
        n = 2 * rnd.next(2, 8);
        char low = char(rnd.next(int('A'), int('X')));
        char high = char(rnd.next(int(low), min(int('Z'), int(low) + 2)));
        while (int(names.size()) < n) {
            names.insert(randomName(1, 30, low, high));
        }
    } else {
        n = 2 * rnd.next(3, 12);
    }

    while (int(names.size()) < n) {
        names.insert(randomName(1, 18));
    }

    vector<string> result(names.begin(), names.end());
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 6);
    for (int tc = 0; tc < cases; ++tc) {
        vector<string> names = buildCase(rnd.next(0, 4));
        println(int(names.size()));
        for (const string& name : names) {
            println(name);
        }
    }
    println(0);

    return 0;
}
