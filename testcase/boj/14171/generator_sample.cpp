#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Entry {
    string city;
    string state;
};

string codeFromIndex(int x) {
    return string{char('A' + (x / 26) % 26), char('A' + x % 26)};
}

string suffixFromIndex(int x) {
    string suffix;
    int length = rnd.next(0, 4);
    for (int i = 0; i < length; ++i) {
        suffix += char('A' + (x + 7 * i + rnd.next(26)) % 26);
    }
    return suffix;
}

bool addEntry(vector<Entry>& entries, set<pair<string, string>>& used, const string& city, const string& state) {
    if (used.count({city, state}) != 0) return false;
    used.insert({city, state});
    entries.push_back({city, state});
    return true;
}

void addUniqueWithPrefix(vector<Entry>& entries,
                         set<pair<string, string>>& used,
                         const string& prefix,
                         const string& state,
                         int salt) {
    for (int attempt = 0; attempt < 80; ++attempt) {
        string city = prefix + suffixFromIndex(salt + attempt);
        if (addEntry(entries, used, city, state)) return;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Entry> entries;
    set<pair<string, string>> used;

    int mode = rnd.next(0, 4);
    int pairGroups = rnd.next(1, 8);
    int salt = rnd.next(1000000);

    for (int i = 0; i < pairGroups; ++i) {
        string a = codeFromIndex((2 * i + salt) % 676);
        string b = codeFromIndex((2 * i + salt + 53) % 676);
        if (a == b) b = codeFromIndex((2 * i + salt + 54) % 676);

        int leftCount = rnd.next(1, mode == 1 ? 5 : 3);
        int rightCount = rnd.next(1, mode == 1 ? 5 : 3);
        for (int j = 0; j < leftCount; ++j) addUniqueWithPrefix(entries, used, a, b, salt + 100 * i + j);
        for (int j = 0; j < rightCount; ++j) addUniqueWithPrefix(entries, used, b, a, salt + 200 * i + j);

        if (mode >= 2) {
            addUniqueWithPrefix(entries, used, a, a, salt + 300 * i);
            addUniqueWithPrefix(entries, used, b, b, salt + 400 * i);
        }
    }

    int noiseCount = rnd.next(0, mode == 4 ? 25 : 10);
    for (int i = 0; i < noiseCount; ++i) {
        string prefix = codeFromIndex((salt + 17 * i + 211) % 676);
        string state = codeFromIndex((salt + 31 * i + 419) % 676);
        addUniqueWithPrefix(entries, used, prefix, state, salt + 500 + i);
    }

    if (mode == 3) {
        string city = "RIVERSIDE";
        addEntry(entries, used, city, "CA");
        addEntry(entries, used, city, "NY");
    }

    shuffle(entries.begin(), entries.end());

    println(static_cast<int>(entries.size()));
    for (const Entry& entry : entries) {
        println(entry.city, entry.state);
    }

    return 0;
}
