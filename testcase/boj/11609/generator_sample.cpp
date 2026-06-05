#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string randomName(int minLen, int maxLen) {
    int len = rnd.next(minLen, maxLen);
    string name;
    name += char('A' + rnd.next(26));
    for (int i = 1; i < len; ++i) {
        name += char('a' + rnd.next(26));
    }
    return name;
}

string fromPool(const vector<string>& values, int minLen, int maxLen) {
    if (!values.empty() && rnd.next(100) < 75) {
        return rnd.any(values);
    }
    return randomName(minLen, maxLen);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> firstPool = {
        "Alice", "Bob", "Carol", "Dave", "Eve", "Mallory", "Oscar", "Peggy"
    };
    vector<string> lastPool = {
        "Adams", "Brown", "Jones", "Kim", "Lee", "Smith", "Taylor", "Young"
    };

    int mode = rnd.next(5);
    int n = 1;
    int minLen = 2;
    int maxLen = 10;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(4, 18);
        lastPool = {randomName(2, 10)};
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        firstPool = {randomName(2, 10)};
    } else if (mode == 3) {
        n = rnd.next(6, 24);
        firstPool = {"Anna", "Anne", "Ann", "Anny", "Bob", "Bobby"};
        lastPool = {"Adam", "Adams", "Adamsa", "Brown", "Browne", "Browns"};
    } else {
        n = rnd.next(10, 35);
        minLen = 8;
        maxLen = 10;
    }

    vector<pair<string, string>> names;
    set<pair<string, string>> seen;
    while ((int)names.size() < n) {
        string first = fromPool(firstPool, minLen, maxLen);
        string last = fromPool(lastPool, minLen, maxLen);
        pair<string, string> candidate = {first, last};
        if (seen.insert(candidate).second) {
            names.push_back(candidate);
        }
    }

    shuffle(names.begin(), names.end());

    println(n);
    for (const auto& name : names) {
        println(name.first, name.second);
    }

    return 0;
}
