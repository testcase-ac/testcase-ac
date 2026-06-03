#include "testlib.h"
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

static string randomName(int maxLen) {
    int len = rnd.next(1, maxLen);
    string s;
    for (int i = 0; i < len; ++i) s += char('a' + rnd.next(0, 25));
    return s;
}

static string indexedName(const string& prefix, int index) {
    string s = prefix;
    do {
        s += char('a' + index % 26);
        index /= 26;
    } while (index > 0);
    if ((int)s.size() > 20) s.resize(20);
    return s;
}

static void addPair(vector<pair<string, string>>& pairs, set<pair<string, string>>& seen,
                    const string& mentor, const string& mentee) {
    if (seen.insert({mentor, mentee}).second) pairs.push_back({mentor, mentee});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<pair<string, string>> pairs;
    set<pair<string, string>> seen;

    if (mode == 0) {
        string mentor = randomName(5);
        int n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) {
            string mentee = indexedName(rnd.any(vector<string>{"a", "aa", "b", "z"}), i);
            addPair(pairs, seen, mentor, mentee);
        }
    } else if (mode == 1) {
        int mentorCount = rnd.next(2, 8);
        int perMentor = rnd.next(2, 8);
        for (int i = 0; i < mentorCount; ++i) {
            string mentor = indexedName("m", i);
            for (int j = 0; j < perMentor; ++j) {
                string mentee = indexedName(rnd.any(vector<string>{"a", "az", "b", "ba"}), j);
                addPair(pairs, seen, mentor, mentee);
            }
        }
    } else if (mode == 2) {
        int nameCount = rnd.next(2, 9);
        vector<string> names;
        for (int i = 0; i < nameCount; ++i) names.push_back(indexedName("p", i));
        for (string mentor : names) {
            string mentee = rnd.any(names);
            addPair(pairs, seen, mentor, mentee);
            if (rnd.next(0, 1)) addPair(pairs, seen, mentee, mentor);
        }
        addPair(pairs, seen, rnd.any(names), rnd.any(names));
    } else if (mode == 3) {
        int n = rnd.next(4, 40);
        for (int i = 0; i < n; ++i) {
            string mentor = indexedName(rnd.any(vector<string>{"a", "aa", "ab", "b"}), rnd.next(0, 12));
            string mentee = indexedName(rnd.any(vector<string>{"x", "xy", "xz", "y"}), rnd.next(0, 12));
            addPair(pairs, seen, mentor, mentee);
        }
    } else {
        int n = rnd.next(1, 60);
        while ((int)pairs.size() < n) {
            addPair(pairs, seen, randomName(20), randomName(20));
        }
    }

    shuffle(pairs.begin(), pairs.end());

    println((int)pairs.size());
    for (auto [mentor, mentee] : pairs) println(mentor, mentee);

    return 0;
}
